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

void cross_val(){
TMVA::Tools::Instance();


vector<string> channel={"1u1e","2u0e","1u1ep1em","1u1up1um","1e1up1um"};


cout<<channel.at(0)<<endl;


for (int mode = 0; mode <1; mode++){
	vector<string> path_sig;
  vector<string> feature_list;
	if (mode<=1){
    path_sig={"wh"};
    feature_list ={"MET","njet","nSRjet","sumPt_SRjet","lep1_pt","lep1_eta","lep2_pt","lep2_eta","jet1_pt","jet1_eta","jet1_m","HWjj_pt","HWjj_eta","HWjj_m","SRjet1_pt","SRjet1_eta","SRjet1_m","SRjet2_pt","SRjet2_eta","SRjet2_m","HBoson_jj_pt","HBoson_jj_eta","HBoson_jj_m","all_vis_jj_pt","all_vis_jj_eta","all_vis_jj_m","HBoson_LRj_pt","HBoson_LRj_eta","HBoson_LRj_m","all_vis_LRj_pt","all_vis_LRj_eta","all_vis_LRj_m","dR_SRjet1_HWlep","dR_SRjet2_HWlep","dR_lep1_lep2","dR_jet1_HWjj","dR_jet1_lep1","dR_jet1_lep2","dR_HWjj_lep1","dR_HWjj_lep2","METSig"};
  }
	else if (mode==2){
    path_sig={"qqZee","ggZee"};
    feature_list = {"MET", "njet", "nSRjet", "sumPt_SRjet", "ep_pt", "ep_eta", "em_pt", "em_eta", "u1_pt", "u1_eta", "jet1_pt", "jet1_eta", "jet1_m", "HWjj_pt", "HWjj_eta", "HWjj_m", "SRjet1_pt", "SRjet1_eta", "SRjet1_m", "SRjet2_pt", "SRjet2_eta", "SRjet2_m", "ZBoson_pt", "ZBoson_eta", "ZBoson_m", "HBoson_jj_pt", "HBoson_jj_eta", "HBoson_jj_m", "all_vis_jj_pt", "all_vis_jj_eta", "all_vis_jj_m", "HBoson_LRj_pt", "HBoson_LRj_eta", "HBoson_LRj_m", "all_vis_LRj_pt", "all_vis_LRj_eta", "all_vis_LRj_m", "HWlep_mT", "HBoson_jj_mT", "HBoson_LRj_mT", "dR_SRjet1_HWlep", "dR_SRjet2_HWlep", "dR_u1ep", "dR_u1em", "dR_epem", "dR_jet1_HWjj", "dR_j1u1", "dR_j1ep", "dR_j1em", "dR_HWjj_ep", "dR_HWjj_em", "dR_HWjj_u1", "dR_ZBoson_HWlep", "dR_ZBoson_HWjj", "METSig"};
  }
	else if (mode==3){
    path_sig={"qqZmumu","ggZmumu"};
    feature_list = {"MET", "njet", "nSRjet", "sumPt_SRjet", "up_pt", "up_eta", "um_pt", "um_eta", "u3_pt", "u3_eta", "jet1_pt", "jet1_eta", "jet1_m", "HWjj_pt", "HWjj_eta", "HWjj_m", "SRjet1_pt", "SRjet1_eta", "SRjet1_m", "SRjet2_pt", "SRjet2_eta", "SRjet2_m", "ZBoson_pt", "ZBoson_eta", "ZBoson_m", "HBoson_jj_pt", "HBoson_jj_eta", "HBoson_jj_m", "all_vis_jj_pt", "all_vis_jj_eta", "all_vis_jj_m", "HBoson_LRj_pt", "HBoson_LRj_eta", "HBoson_LRj_m", "all_vis_LRj_pt", "all_vis_LRj_eta", "all_vis_LRj_m", "HWlep_mT", "HBoson_jj_mT", "HBoson_LRj_mT", "dR_SRjet1_HWlep", "dR_SRjet2_HWlep", "dR_u3up", "dR_u3um", "dR_upum", "dR_jet1_HWjj", "dR_j1u3", "dR_j1up", "dR_j1um", "dR_HWjj_up", "dR_HWjj_um", "dR_HWjj_u3", "dR_ZBoson_HWlep", "dR_ZBoson_HWjj", "METSig"};
  }
  else if (mode>=4){
    path_sig={"qqZmumu","ggZmumu"};
    feature_list = {"MET", "njet", "nSRjet", "sumPt_SRjet", "up_pt", "up_eta", "um_pt", "um_eta", "ele1_pt", "ele1_eta", "jet1_pt", "jet1_eta", "jet1_m", "HWjj_pt", "HWjj_eta", "HWjj_m", "SRjet1_pt", "SRjet1_eta", "SRjet1_m", "SRjet2_pt", "SRjet2_eta", "SRjet2_m", "ZBoson_pt", "ZBoson_eta", "ZBoson_m", "HBoson_jj_pt", "HBoson_jj_eta", "HBoson_jj_m", "all_vis_jj_pt", "all_vis_jj_eta", "all_vis_jj_m", "HBoson_LRj_pt", "HBoson_LRj_eta", "HBoson_LRj_m", "all_vis_LRj_pt", "all_vis_LRj_eta", "all_vis_LRj_m", "HWlep_mT", "HBoson_jj_mT", "HBoson_LRj_mT", "dR_SRjet1_HWlep", "dR_SRjet2_HWlep", " dR_e1up", "dR_e1um", "dR_upum", "dR_jet1_HWjj", "dR_j1e1", "dR_j1up", "dR_j1um", "dR_HWjj_up", "dR_HWjj_um", "dR_HWjj_e1", "dR_ZBoson_HWlep", "dR_ZBoson_HWjj", "METSig"};
  }

	vector<string> path_bkg={"diboson","top","Wjets","Zjets"};
   if (mode==4){path_bkg={"diboson","top","Zjets"};}

	string path1="/home/student/ML_lvqq/ML_data/";
	vector<string> cut={"1u1e_",
	"2u0e_",
	"1u1ep1em_Ele2ID_",
	"1u1up1um_Muon3ID_",
	"1e1up1um_Ele1ID_",
   };
	 
	string path2="/ntuple_";
	string path3=".root";

  TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset_"+channel.at(mode));

	for (int i = 0; i <path_sig.size(); i++){
    // cout<<path1+channel.at(mode)+path2+cut.at(mode)+path_sig.at(i)+path3<<endl;
    TString path = (TString)(path1+channel.at(mode)+path2+cut.at(mode)+path_sig.at(i)+path3);
    cout<<path<<endl;
		TFile *input = TFile::Open(path);
		cout << "--- TMVAClassification       : Using input sig file: " << input->GetName() << endl;
		TTree *mPlusJ    = (TTree*)input->Get("mPlusJ");
		TTree *mMinusJ     = (TTree*)input->Get("mMinusJ");
		Double_t signalWeight     = 1.0;
		dataloader->AddSignalTree    ( mPlusJ,     signalWeight );
		dataloader->AddSignalTree    ( mMinusJ,     signalWeight );
	}
	for (int i = 0; i <path_bkg.size(); i++){
    TString path = (TString)(path1+channel.at(mode)+path2+cut.at(mode)+path_bkg.at(i)+path3);
    cout<<path<<endl;
		TFile *input = TFile::Open(path);
		cout << "--- TMVAClassification       : Using input bkg file: " << input->GetName() << endl;
		TTree *mPlusJ    = (TTree*)input->Get("mPlusJ");
		TTree *mMinusJ     = (TTree*)input->Get("mMinusJ");
		Double_t backgroundWeight = 1.0;
		dataloader->AddBackgroundTree( mPlusJ, backgroundWeight );
		dataloader->AddBackgroundTree( mMinusJ, backgroundWeight );
	}
  TString outfileName( "TMVA_CV_"+channel.at(mode)+".root" );
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
 
  for (int i = 0; i <feature_list.size(); i++){
     cout<<feature_list.at(i)<<endl;
  	  dataloader->AddVariable( feature_list.at(i), 'F' );
  }
  // dataloader->SetBackgroundWeightExpression( "weight" );
  dataloader->PrepareTrainingAndTestTree("","","nTest_Signal=0"":nTest_Background=0");
  
	TString opt = "!V:Silent:!Correlations"":AnalysisType=Classification"":NumFolds=2";
	TMVA::CrossValidation cv {"CV_jobname", dataloader, outputFile, opt};
// cv.BookMethod(TMVA::Types::kBDT, "BDT","!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
cv.BookMethod(TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

  
  // Save the output
  outputFile->Close();
  
  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TMVAClassification is done!" << std::endl;
  
  delete dataloader;
}

// Launch the GUI for the root macros
// if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );

return 0;
}







