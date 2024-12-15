#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"
#include "TMVA/CrossValidation.h"
using namespace std;

void cross_val_test(){
TMVA::Tools::Instance();
TFile *input(0);
 TString fname = "./tmva_class_example.root";
 if (!gSystem->AccessPathName( fname )) {
    input = TFile::Open( fname ); // check if file in local directory exists
 }
 else {
    TFile::SetCacheFileDir(".");
    input = TFile::Open("http://root.cern.ch/files/tmva_class_example.root", "CACHEREAD");
 }
 if (!input) {
    std::cout << "ERROR: could not open data file" << std::endl;
    exit(1);
 }
 std::cout << "--- TMVAClassification       : Using input file: " << input->GetName() << std::endl;
// Register the training and test trees

 TTree *signalTree     = (TTree*)input->Get("TreeS");
 TTree *background     = (TTree*)input->Get("TreeB");

 // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
 TString outfileName( "TMVA.root" );
 TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
 // TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,                                             "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

  TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");

  dataloader->AddVariable( "myvar1 := var1+var2", 'F' );
  dataloader->AddVariable( "myvar2 := var1-var2", "Expression 2", "", 'F' );
  dataloader->AddVariable( "var3",                "Variable 3", "units", 'F' );
  dataloader->AddVariable( "var4",                "Variable 4", "units", 'F' );

  // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;

   // You can add an arbitrary number of signal or background trees
   dataloader->AddSignalTree    ( signalTree,     signalWeight );
   dataloader->AddBackgroundTree( background, backgroundWeight );

  dataloader->SetBackgroundWeightExpression( "weight" );

   // Apply additional cuts on the signal and background samples (can be different)
   TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";
  dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,
                                        "nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V" );

  TString opt = "!V:!Silent:!Correlations"
":AnalysisType=Classification"
":NumFolds=2";
TMVA::CrossValidation cv {"cross_val_job", dataloader, outputFile, opt};
cv.BookMethod(TMVA::Types::kBDT, "BDT","!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
cv.Evaluate();

  
  // factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT","!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
  // // Train MVAs using the set of training events
  //  factory->TrainAllMethods();

  //  // Evaluate all MVAs using the set of test events
  //  factory->TestAllMethods();

  //  // Evaluate and compare performance of all configured MVAs
  //  factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   // delete factory;
   delete dataloader;
   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );

   return 0;
}