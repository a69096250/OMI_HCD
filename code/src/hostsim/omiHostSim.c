/*
 *****************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *****************************************************************************
 *  File        : omiHostSim.c 
 *  Date        : 2020-02-24
 *  Description : Simple application to test an OMI Library
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "omiDef.h"
#include "omiIft.h"



#define PARAM_LEN       16
#define LINE_LEN      1024
#define MOD_SIZE      1000
#define INST_SIZE      100
#define UDF_MAX_ARGS    16

void strip(char *head)
// Basic strip function that erases some trailing characters
// from the end of a string.
{
  char *tail;
  tail=head;
  while (*tail!=(char)0) {
    tail++;
  }
  while (tail!=head && (*tail)==(char)0) {
    //printf("%s\n",head);
    tail--;
    if (*tail==(char)13)  *tail=(char)0; // CR
    if (*tail==(char)10)  *tail=(char)0; // LF
    if (*tail==(char)32)  *tail=(char)0; // Space
    if (*tail==(char)9)   *tail=(char)0; // Tab
  }
}

void insertInArray(char *param, double value, char **paramArray, 
                  double *valueArray, int *arraySize, int arrayMax)
{
  int i;
  //printf("insert %s %d\n",param,*arraySize);
  for (i=0; i < *arraySize; i++) {
    if (!strcmp(param,paramArray[i])) {
      // Parameter found
      // Modify array & return
      valueArray[i]=value;
      return;
    }
  }
  // Parameter not found
  // Append to array
  if (*arraySize == arrayMax) {
    // If max array size exceeded, print warning and return
    printf("WARNING: Cannot add parameter %s, because it would exceed array size\n",param);
    return;
  }
  strncpy(paramArray[*arraySize],param,PARAM_LEN);
  valueArray[*arraySize]=value;
  *arraySize=*arraySize+1;
  return;
}


int main(int argc, char *argv[])
{
  FILE *fp;
  int i;

  char inst_param_array[INST_SIZE][PARAM_LEN];
  char *inst_param[INST_SIZE];
  double inst_value[INST_SIZE];
  char mod_param_array[MOD_SIZE][PARAM_LEN];
  char *mod_param[MOD_SIZE];
  double mod_value[MOD_SIZE];
  char omiInput[LINE_LEN];
  char omiOutput[LINE_LEN];
  char degFile[LINE_LEN];
  char omiSort[LINE_LEN];
  char modelName[PARAM_LEN];
  char instName[PARAM_LEN];
  omiCKT CKT;
  omiModel Model;
  omiInstance Instance;
  omiIft *pIft;
  omiEvalData EvalData;
  omiSelectModelBin SelectModelBin;
  char **coreDataParam=(char**)0;
  int coreDataSize=0;

  char line[LINE_LEN];
  char *lvalue, *rvalue, *arg1, *arg2, *arg3, *arg4, *cmd, *index, *cmdfile;
  double dvalue,tolerance,udfOutput;
  int ivalue,pcount,retval, verbose;
  double udfArgs[UDF_MAX_ARGS];

  for (i=0;i<INST_SIZE;i++)
    inst_param[i]=inst_param_array[i];
  for (i=0;i<MOD_SIZE;i++)
    mod_param[i]=mod_param_array[i];


  CKT.omiInput=(char*)omiInput;
  CKT.omiOutput=(char*)omiOutput;
  CKT.degFile=(char*)degFile;
  CKT.omiSort=(char*)omiSort;
  Instance.instName=(char*)instName;
  Instance.param=(char**)inst_param;
  Instance.value=(double*)inst_value;
  Instance.instSize=0;
  Model.modelName=(char*)modelName;
  Model.param=(char**)mod_param;
  Model.value=(double*)mod_value;
  Model.modelSize=0;
  Model.bin=&SelectModelBin;
  CKT.print=printf;
  EvalData.workData=(double*)0;
  EvalData.specData=(void*)0;
  EvalData.coreData=(void*)0;
  EvalData.probeData=(omiProbeData*)0;
  EvalData.noiseData=(omiNoiseData*)0;

  verbose=0;
  cmdfile="host.cmd";
  for (i=1;i<argc;i++) {
    if (!strcmp(argv[i],"-verbose") || !strcmp(argv[i],"-v")) {
      verbose=1;
      continue;
    }
    cmdfile=argv[i];
  }
  

  fp=fopen(cmdfile,"r");
  if (!fp) {
    printf("ERROR: Could not open command-file %s\n",cmdfile);
    exit(1);
  }
  while ( fgets(line,LINE_LEN,fp)!=NULL ) {
    if (strlen(line)==0)
      continue;
    if (line[0]=='#') {
      //printf("Comment\n");
      continue; // Skip comments
    }
    strip(line);
    //printf("Line: %s\n",line);
    lvalue=strtok(line,"=");
    rvalue=strtok(NULL,"=");
    if (rvalue!=NULL) {
      if (sscanf(rvalue,"%lf",&dvalue)==1) {
        ivalue=(int)dvalue;
      } else {
        ivalue=0;
        dvalue=0;
      }
      //printf("%s=%s %d %le\n",lvalue,rvalue,ivalue,dvalue);
      if (strlen(rvalue)==0) {
        printf("WARNING: Could not parse: %s\n",line);
        continue;
      }
      // Process array values
      if (lvalue[strlen(lvalue)-1]==']') {
        lvalue[strlen(lvalue)-1]=(char)0;
        strtok(lvalue,"[");
        index=strtok(NULL,"[");
        if (index==NULL) {
          printf("WARNING: Could not find voltage index\n");
          continue;
        }
        //printf("array %s %s %s\n",lvalue,index,rvalue);
        if (!strcmp(lvalue,"Model.param")) {
          insertInArray(index,dvalue,Model.param,Model.value,
                        &Model.modelSize,MOD_SIZE); 
          continue;          
	}
        if (!strcmp(lvalue,"Instance.param")) {
          insertInArray(index,dvalue,Instance.param,Instance.value,
                        &Instance.instSize,INST_SIZE); 
          continue;          
	}
        if (!strcmp(lvalue,"CoreData")) {
          insertInArray(index,dvalue,coreDataParam,EvalData.coreData,
                        &coreDataSize,coreDataSize); 
          continue;          
	}
        if (!strcmp(lvalue,"V")) {
          if (sscanf(index,"%d",&i)<1) {
            printf("WARNING: Could not parse voltage index\n");
            continue;
          }
          if (i>pIft->workDataSize/sizeof(double)) {
            printf("WARNING: Voltage index exceeds WorkData max index\n");
            continue;
          }
          EvalData.workData[i]=dvalue;
          continue;
        }
        printf("WARNING: Could not find array named %s\n",lvalue);
        continue;
      }
      // Process scalar values
      if (!strcmp(lvalue,"CKT.CKTtemp")) {
	CKT.CKTtemp=dvalue;
        continue;
      }
      if (!strcmp(lvalue,"CKT.CKTnomTemp")) {
	CKT.CKTnomTemp=dvalue;
        continue;
      }
      if (!strcmp(lvalue,"CKT.scale")) {
	CKT.scale=dvalue;
        continue;
      }
      if (!strcmp(lvalue,"CKT.scalm")) {
	CKT.scalm=dvalue;
        continue;
      }
      if (!strcmp(lvalue,"CKT.evalType")) {
	CKT.evalType=ivalue;
        continue;
      }
      if (!strcmp(lvalue,"CKT.spiceType")) {
	CKT.spiceType=ivalue;
        continue;
      }
      if (!strcmp(lvalue,"CKT.omiAge")) {
	CKT.omiAge=ivalue;
        continue;
      }
      if (!strcmp(lvalue,"CKT.tblSize")) {
	CKT.tblSize=ivalue;
        continue;
      }
      if (!strcmp(lvalue,"CKT.omiInput")) {
        if (!strcmp(rvalue,"(null)")) {
          CKT.omiInput=NULL;
	} else {
          strcpy(omiInput,rvalue);
          CKT.omiInput=omiInput;
	}
        continue;
      }
      if (!strcmp(lvalue,"CKT.omiOutput")) {
        if (!strcmp(rvalue,"(null)")) {
          CKT.omiOutput=NULL;
	} else {
          strcpy(omiOutput,rvalue);
          CKT.omiOutput=omiOutput;
	}
        continue;
      }
      if (!strcmp(lvalue,"CKT.omiSave")) {
	CKT.omiSave=ivalue;
        continue;
      }
      if (!strcmp(lvalue,"CKT.degFile")) {
        if (!strcmp(rvalue,"(null)")) {
          CKT.degFile=NULL;
	} else {
          strcpy(degFile,rvalue);
          CKT.degFile=degFile;
	}
        continue;
      }
      if (!strcmp(lvalue,"CKT.omiSort")) {
        if (!strcmp(rvalue,"(null)")) {
          CKT.omiSort=NULL;
	} else {
          strcpy(omiSort,rvalue);
          CKT.omiSort=omiSort;
	}
        continue;
      }
      if (!strcmp(lvalue,"Model.id")) {
	Model.id=ivalue;
        continue;
      }
      if (!strcmp(lvalue,"Model.modelType")) {
	Model.modelType=ivalue;
        continue;
      }
      if (!strcmp(lvalue,"Model.level")) {
	Model.level=ivalue;
        continue;
      }
      if (!strcmp(lvalue,"Model.printModel")) {
	Model.printModel=ivalue;
        continue;
      }
      if (!strcmp(lvalue,"Model.modelName")) {
	strcpy(modelName,rvalue);
        continue;
      }
      if (!strcmp(lvalue,"Model.bin.dlmin")) {
	SelectModelBin.dlmin=dvalue;
        continue;
      }
      if (!strcmp(lvalue,"Model.bin.dlmax")) {
	SelectModelBin.dlmax=dvalue;
        continue;
      }
      if (!strcmp(lvalue,"Model.bin.dwmin")) {
	SelectModelBin.dwmin=dvalue;
        continue;
      }
      if (!strcmp(lvalue,"Model.bin.dwmax")) {
	SelectModelBin.dwmax=dvalue;
        continue;
      }
      if (!strcmp(lvalue,"Instance.printWarn")) {
	Instance.printWarn=ivalue;
        continue;
      }
      if (!strcmp(lvalue,"Instance.instName")) {
	strcpy(instName,rvalue);
        continue;
      }
      if (!strcmp(lvalue,"EvalData.evalI")) {
	EvalData.evalI=ivalue;
        continue;
      }
      if (!strcmp(lvalue,"EvalData.evalQ")) {
	EvalData.evalQ=ivalue;
        continue;
      }
      if (!strcmp(lvalue,"EvalData.freq")) {
	EvalData.freq=dvalue;
        continue;
      }
      if (!strcmp(lvalue,"EvalData.gmin")) {
	EvalData.gmin=dvalue;
        continue;
      }

      printf("WARNING: Unrecognized field: %s\n",lvalue);
      continue;
    }
    cmd=strtok(line," ");
    arg1=strtok(NULL," ");
    arg2=strtok(NULL," ");
    arg3=strtok(NULL," ");
    arg4=strtok(NULL," ");
    if (cmd==NULL)
      continue;
    if (!strcmp(cmd,"Update")) {
      retval=omiUpdate(&CKT,&Model,&Instance);
      if (retval==1) printf("ERROR: omiUpdate returned OMI_ERROR\n");
      if (retval!=1 && verbose) printf("omiUpdate returned %d\n",retval);
      continue;
    }
    if (!strcmp(cmd,"Create")) {
      pIft=(omiIft*)omiCreate(CKT.spiceType,Model.id,Model.level,Model.pModelData);
      if (verbose) printf("omiCreate returned 0x%x\n",pIft);
      if (EvalData.workData)
        free(EvalData.workData);
      if (pIft->workDataSize>0)
        EvalData.workData=(double*)malloc(pIft->workDataSize);
      else
        EvalData.workData=(double*)0;
      if (EvalData.specData)
        free(EvalData.specData);
      if (pIft->specDataSize>0)
        EvalData.specData=malloc(pIft->specDataSize);
      else
        EvalData.specData=(void*)0;
      if (EvalData.probeData)
        free(EvalData.probeData);
      if (pIft->probeDataSize>0)
        EvalData.probeData=(omiProbeData*)malloc(sizeof(omiProbeData)*pIft->probeDataSize);
      else
        EvalData.probeData=(omiProbeData*)0;
      if (EvalData.noiseData)
        free(EvalData.noiseData);
      if (pIft->noiseDataSize>0)
        EvalData.noiseData=(omiNoiseData*)malloc(sizeof(omiNoiseData)*pIft->noiseDataSize);
      else
        EvalData.noiseData=(omiNoiseData*)0;
      continue;
    }
    if (!strcmp(cmd,"Integrate")) {
      if (sscanf(arg1,"%lf",&dvalue)<1) {
        printf("WARNING: Could not parse time for omiIntegrate\n");
        continue;
      } else {
        EvalData.time=dvalue;
      }
      if (sscanf(arg2,"%lf",&dvalue)<1) {
        printf("WARNING: Could not parse step for omiIntegrate\n");
        continue;
      } else {
        EvalData.step=dvalue;
      }
      retval=pIft->omiIntegrate(Model.pModelData,Instance.pInstData,&EvalData);
      if (retval==1) printf("ERROR: omiIntegrate returned %d\n",retval);
      if (retval!=1 && verbose) printf("omiIntegrate returned %d\n",retval);
      continue;
    }
    if (!strcmp(cmd,"PrintAge")) {
      retval=omiPrintAge(&CKT);
      if (retval==1) printf("ERROR: omiPrintAge returned OMI_ERROR\n");
      if (retval!=1 && verbose) printf("omiPrintAge returned %d\n",retval);
      continue;
    }
    if (!strcmp(cmd,"FreeAge")) {
      retval=omiFreeAge();
      if (retval==1) printf("ERROR: omiFreeAge returned OMI_ERROR\n");
      if (retval!=1 && verbose) printf("omiFreeAge returned %d\n",retval);
      continue;
    }
    if (!strcmp(cmd,"CopyCoreDataParam")) {
      //printf("CopyCoreDataParam\n");
      coreDataSize=Model.modelSize_o;
      coreDataParam=Model.param_o;
      if (EvalData.coreData)
        free(EvalData.coreData);
      EvalData.coreData=(double*)malloc(sizeof(double)*coreDataSize);
      //printf("CoreData: size=%d",coreDataSize);
      //for (i=0; i<coreDataSize; i++) printf(" %s",coreDataParam[i]);
      //printf("\n");
      continue;
    }
    if (!strcmp(cmd,"print")) {
      if (arg1 == NULL) {
        printf("WARNING: Ignoring print command with NULL arguments\n");
        continue;
      }
      if (!strcmp(arg1,"Udf")) {
        printf("omiUdf output = %le\n",udfOutput);
        continue;
      }
      if (arg2 == NULL) {
        printf("WARNING: Ignoring print command with fewer than two arguments\n");
        continue;
      }
      if (!strcmp(arg1,"Model.param_o")) {
        for (pcount=0;pcount<Model.modelSize_o;pcount++) {
          if (!strcmp(Model.param_o[pcount],arg2)) {
	    printf("%s=%le\n",arg2,Model.value_o[pcount]);
            break;
	  }
	}
        if (pcount==Model.modelSize_o) {
          printf("Could not find output model parameter: %s\n",arg2);
        }
        continue;
      }
      if (!strcmp(arg1,"Instance.param_o")) {
        for (pcount=0;pcount<Instance.instSize_o;pcount++) {
          if (!strcmp(Instance.param_o[pcount],arg2)) {
	    printf("%s=%le\n",arg2,Instance.value_o[pcount]);
            break;
	  }
	}
        if (pcount==Instance.instSize_o) {
          printf("Could not find output instance parameter: %s\n",arg2);
        }
        continue;
      }
      printf("WARNING: Unsupported print field: %s",arg1);
      continue;
    }
    if (!strcmp(cmd,"assert")) {
      if (arg1 == NULL || arg2 == NULL || arg3 == NULL) {
        printf("WARNING: Ignoring assert command with NULL arguments\n");
        continue;
      }
      if (!strcmp(arg1,"Udf")) {
        if (sscanf(arg2,"%lf",&dvalue)<1) {
          printf("WARNING: Could not parse assert value for omiUdf\n");
          continue;
	}
        if (sscanf(arg3,"%lf",&tolerance)<1) {
          printf("WARNING: Could not parse assert tolerance for omiUdf\n");
          continue;
	}
        if (fabs(udfOutput-dvalue)>fabs(tolerance)) { 
	  printf("FAILED omiUdf output = %s (tolerance %s)\n",arg2,arg3);
          continue;
	}
	printf("PASSED omiUdf output = %s (tolerance %s)\n",arg2,arg3);
        continue;
      }
      if (arg4 == NULL) {
        printf("WARNING: Ignoring assert command with fewer than four arguments\n");
        continue;
      }
      if (!strcmp(arg1,"Model.param_o")) {
        for (pcount=0;pcount<Model.modelSize_o;pcount++) {
          if (!strcmp(Model.param_o[pcount],arg2)) {
            if (sscanf(arg3,"%lf",&dvalue)<1) {
              printf("WARNING: Could not parse assert value for model parameter %s\n",arg2);
              break;
	    }
            if (sscanf(arg4,"%lf",&tolerance)<1) {
              printf("WARNING: Could not parse assert tolerance for model parameter %s\n",arg2);
              break;
	    }
            if (fabs(Model.value_o[pcount]-dvalue)>fabs(tolerance)) { 
	      printf("FAILED %s %s = %s (tolerance %s)\n",arg1,arg2,arg3,arg4);
              break;
	    }
	    printf("PASSED %s %s = %s (tolerance %s)\n",arg1,arg2,arg3,arg4);
            break;

	  }
	}
        if (pcount==Model.modelSize_o) {
          printf("Could not find output model parameter: %s\n",arg2);
        }
        continue;
      }
      if (!strcmp(arg1,"Instance.param_o")) {
        for (pcount=0;pcount<Instance.instSize_o;pcount++) {
          if (!strcmp(Instance.param_o[pcount],arg2)) {
            if (sscanf(arg3,"%lf",&dvalue)<1) {
              printf("WARNING: Could not parse assert value for instance parameter %s\n",arg2);
              break;
	    }
            if (sscanf(arg4,"%lf",&tolerance)<1) {
              printf("WARNING: Could not parse assert tolerance for instance parameter %s\n",arg2);
              break;
	    }
            if (fabs(Instance.value_o[pcount]-dvalue)>fabs(tolerance)) { 
	      printf("FAILED %s %s = %s (tolerance %s)\n",arg1,arg2,arg3,arg4);
              break;
	    }
	    printf("PASSED %s %s = %s (tolerance %s)\n",arg1,arg2,arg3,arg4);
            break;

	  }
	}
        if (pcount==Instance.instSize_o) {
          printf("Could not find output instance parameter: %s\n",arg2);
        }
        continue;
      }
      printf("WARNING: Unsupported assert field: %s\n",arg1);
      continue;
    }
    if (!strcmp(cmd,"Udf")) {
      for (i=0; i<UDF_MAX_ARGS; i++) {
        udfArgs[i]=OMI_AUNDEF;
      }
      if (sscanf(arg2,"%d",&ivalue)!=1) {
        printf("WARNING: Could not parse numArgs for omiUdf from %s\n",arg2);
        ivalue=0;
      }
      if (ivalue > UDF_MAX_ARGS) {
        printf("WARNING: hostsim supports only %d arguments of type double,\n",UDF_MAX_ARGS);
        printf("but %d arguments were specified.  Remaining arguments will\n",ivalue);
        printf("be ignored.  Please increase UDF_MAX_ARGS and recompile\n");
        printf("hostsim to support this behavior.\n");
        ivalue = UDF_MAX_ARGS;
      }
      if (ivalue >= 1) {
        if (sscanf(arg3,"%lf",&dvalue)!=1) {
          printf("WARNING: Could not parse omiUdf arg 1 from %s\n",arg3);
          dvalue=0;
        }
        udfArgs[0]=dvalue;
      }
      if (ivalue >= 2) {
        if (sscanf(arg4,"%lf",&dvalue)!=1) {
          printf("WARNING: Could not parse omiUdf arg 2 from %s\n",arg4);
          dvalue=0;
        }
        udfArgs[1]=dvalue;
      }
      for (i=2; i<ivalue; i++) {
        arg4=strtok(NULL," ");
        if (sscanf(arg4,"%lf",&dvalue)!=1) {
          printf("WARNING: Could not parse omiUdf arg %d from %s\n",i+1,arg4);
          dvalue=0;
        }
        udfArgs[i]=dvalue;
      }
      retval=omiUdf(&udfOutput,arg1,ivalue,(double*)udfArgs);
      if (retval==1) printf("ERROR: omiUdf returned status OMI_ERROR and value %e\n",dvalue);
      if (retval!=1 && verbose) printf("omiUdf returned status %d and value %e\n",retval,dvalue);
      continue;
    }
    if (!strcmp(cmd,"FreeUdf")) {
      retval=omiFreeUdf();
      if (retval==1) printf("ERROR: omiFreeUdf returned OMI_ERROR\n");
      if (retval!=1 && verbose) printf("omiFreeUdf returned %d\n",retval);
      continue;
    }



    printf("WARNING: Unrecognized command: %s\n",line);
  }
  fclose(fp);

  if (verbose) printf("hostsim completed\n");
  return 0;
}  
