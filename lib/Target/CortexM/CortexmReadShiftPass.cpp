#include "CortexmReadShiftPass.h"
#include "CodeEmitVisitor.h"

#include <onnc/IR/Compute/Tensor.h>
#include <onnc/IR/Compute/Initializer.h>
#include <onnc/IR/Compute/InputOperator.h>
#include <onnc/IR/Compute/OutputOperator.h>
#include <onnc/Support/Casting.h>
#include <onnc/Support/IOStream.h>
#include <onnc/Support/Timer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace onnc;

extern struct shift_list* first_shift ;

CortexmReadShiftPass::CortexmReadShiftPass(TargetBackend *pBackend, CortexMBackendMeta *pMeta)
  : ModulePass(ID),
    m_pBackend(pBackend), m_pMeta(m_pMeta){
}

Pass::ReturnType CortexmReadShiftPass::runOnModule(Module& pModule){
  FILE *shift_file;
  shift_file = fopen("../src/shift.txt","r");
  char shift_data[50] = "";
  if(!shift_file){
    errs() << "no shift file\n";
  }else{
    fread(shift_data,50,1,shift_file);
    //errs() << shift_data << "\n";
    const char *spilt_char = ",";
    char *all_sub_data;
    all_sub_data = strtok(shift_data , spilt_char);
    while(all_sub_data != NULL){
      //errs() << all_sub_data << "\n";
      int shift_number = atoi(all_sub_data);
      all_sub_data = strtok(NULL,spilt_char);
      errs() << shift_number << "\n";
      //save data
      if(first == 0){
        first_shift = save_shift;
        save_shift -> shift_value = shift_number;
        save_shift -> next = NULL;
        first++;
      }else{
        struct shift_list* new_shift = (shift_list*)malloc(sizeof(shift_list));
        new_shift -> shift_value = shift_number;
        new_shift -> next = NULL;
        save_shift -> next = new_shift;
        save_shift = new_shift;
      }
      //save finish
    }
    fclose(shift_file);
  }

  return Pass::kModuleNoChanged;
}

char CortexmReadShiftPass::ID = 0;

CortexmReadShiftPass *onnc::CreateCortexmReadShiftPass(TargetBackend *pBackend , CortexMBackendMeta *pMeta){
  return new CortexmReadShiftPass(pBackend, pMeta);
}
