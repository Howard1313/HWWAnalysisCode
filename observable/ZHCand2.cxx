#include "HWWAnalysisCode/ZHCand.h"

#include <limits>
#include <string.h>
#include <iostream>
#include <map>
#include "TMath.h"

#include "xAODParticleEvent/CompositeParticleContainer.h"
#include "xAODParticleEvent/ParticleContainer.h"
#include "xAODMissingET/MissingETContainer.h"


// uncomment the following line to enable debug printouts
// #define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);

// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"

ClassImp(ZHCand)

//______________________________________________________________________________________________

ZHCand::ZHCand(){
  // dvalue constructor
  DEBUGclass("dvalue constructor called");
}

//______________________________________________________________________________________________

ZHCand::~ZHCand(){
  // dvalue destructor
  DEBUGclass("destructor called");
} 


#define XAOD_STANDALONE 1
// put here any EDM includes you might need, e.g.
/* example block
#include "xAODParticleEvent/CompositeParticleContainer.h"
*/

//______________________________________________________________________________________________

bool ZHCand::makeCache() const {
  // function that chaches vector that is later retrieved with function getVector()
  // called on every event for every cut and histogram
  
  DEBUGclass("=============================== entering function ===========================");

  // the TQEventObservable only works in an ASG RELEASE, hence
  // we encapsulate the implementation in an ifdef/ifndef block
  #ifndef HAS_XAOD
  #warning "using plain ROOT compilation scheme - please add an ASG Analysis Release in order to use this feature!"
  return std::numeric_limits<double>::quiet_NaN();
  #else
  // in the rest of this function, you should retrieve the data and calculate your return value
  // here is the place where most of your custom code should go
  // a couple of comments should guide you through the process
  // when writing your code, please keep in mind that this code can be executed several times on every event
  // make your code efficient. catch all possible problems. when in doubt, contact experts!

  if (this->getCurrentEntry() == this->fCachedEntry) {
    return true; //nothing to do here, return value already cached
  }

  // clear the old cache before recalculating it for new event
  /* example block
     myvector.clear();
  */

     myvector.clear();
  // first, you can retrieve the data members you need with the 'retrieve' method:
  /* example block:
  // Retrieve CompositeParticle container
  const xAOD::CompositeParticleContainer *cand = 0;
  if(!this->fEvent->retrieve(cand, this->mContName.Data()).isSuccess()){
  DEBUGclass("failed to retrieve candidates!");
  return false;
  }
   */
  // Retrieve CompositeParticle container
  const xAOD::CompositeParticleContainer *cand = 0;
  if(!this->fEvent->retrieve(cand, this->mContName.Data()).isSuccess()){
    DEBUGclass("failed to retrieve candidates!");
    return false;
  }
  DEBUGclass(" sucess retrieved candidates! %s",this->mContName.Data());
  DEBUGclass(" cand->size(): %i",cand->size());
  
  // after you have retrieved your data members, you can proceed to calculate the return value
  // probably, you first have to retrieve an element from the container
  /* example block:
  const xAOD::CompositeParticle *Evt = cand->at(0);
  */
  //scalar sum pt
  float SumPt_SRjet=0;

  std::vector< const xAOD::Jet*> vecjet;
  std::vector< const xAOD::Jet*> vecSRjet;
  std::vector<const xAOD::Muon*> vecmuon;
  std::vector<const xAOD::Muon*> vecmuon_p;
  std::vector<const xAOD::Muon*> vecmuon_m;
  std::vector<const xAOD::Electron*> vecele;
  std::vector<const xAOD::Electron*> vecele_p;
  std::vector<const xAOD::Electron*> vecele_m;
  std::vector<const xAOD::IParticle*> veclep;
    
//1st loop
  DEBUGclass("============================ event info start ===============================");
  const xAOD::CompositeParticle *Evt = cand->at(0);
  for (std::size_t n = 0; n < Evt->nParts(); ++n){
    if (Evt->part(n)->type()==xAOD::Type::Jet) vecjet.push_back(Evt->jet(n));
    
    if (Evt->part(n)->type()==xAOD::Type::Muon){
      const xAOD::Muon *muon = Evt->muon(n);
      int muon_charge = muon->charge();
      if (muon_charge==1) vecmuon_p.push_back(muon);
      if (muon_charge==-1) vecmuon_m.push_back(muon);
      vecmuon.push_back(muon);
      veclep.push_back(muon);
    }
    if (Evt->part(n)->type()==xAOD::Type::Electron){
      const xAOD::Electron* ele=Evt->electron(n);
      int ele_charge = ele->charge();
      if (ele_charge==1) vecele_p.push_back(ele);
      if (ele_charge==-1) vecele_m.push_back(ele);
      vecele.push_back(ele);
      veclep.push_back(ele);
    }    
  }
  float sumPt_SRjet=0;
  for (std::size_t n = 0; n < Evt->nOtherParts(); ++n){
    if (Evt->otherPart(n)->type()==xAOD::Type::Jet){
      const xAOD::Jet *jet = Evt->otherJet(n);
      vecSRjet.push_back(jet);
      sumPt_SRjet+=jet->pt();
    }
    if (Evt->otherPart(n)->type()==xAOD::Type::Muon){
      const xAOD::Muon *muon = Evt->otherMuon(n);
      int muon_charge = muon->charge();
      if (muon_charge==1) vecmuon_p.push_back(muon);
      if (muon_charge==-1) vecmuon_m.push_back(muon);
      vecmuon.push_back(muon);
      veclep.push_back(muon);
    }
    if (Evt->otherPart(n)->type()==xAOD::Type::Electron){
      const xAOD::Electron* ele=Evt->otherElectron(n);
      int ele_charge = ele->charge();
      if (ele_charge==1) vecele_p.push_back(ele);
      if (ele_charge==-1) vecele_m.push_back(ele);
      vecele.push_back(ele);
      veclep.push_back(ele);
    }    
  }


  
  int nmuon=vecmuon.size();
  int nmuon_p=vecmuon_p.size();
  int nmuon_m=vecmuon_m.size();
  int nele=vecele.size();
  int nele_p=vecele_p.size();
  int nele_m=vecele_m.size();
  int njet=vecjet.size();
  int nSRjet=vecSRjet.size();
  int nlep=veclep.size();

  std::sort(vecjet.begin(), vecjet.end(), cmp_pt_Jet );
  std::sort(vecSRjet.begin(), vecSRjet.end(), cmp_pt_Jet );
  std::sort(vecmuon.begin(), vecmuon.end(), cmp_pt_Muon );
  std::sort(vecmuon_p.begin(), vecmuon_p.end(), cmp_pt_Muon );
  std::sort(vecmuon_m.begin(), vecmuon_m.end(), cmp_pt_Muon );
  std::sort(vecele.begin(), vecele.end(), cmp_pt_Electron );
  std::sort(vecele_p.begin(), vecele_p.end(), cmp_pt_Electron );
  std::sort(vecele_m.begin(), vecele_m.end(), cmp_pt_Electron );
  std::sort(veclep.begin(), veclep.end(), cmp_pt_IParticle );

  const xAOD::MissingET *METCand = Evt->missingET();
  TLorentzVector miss(METCand->mpx(),METCand->mpy(),0,METCand->met());

  float dvalue=9999999;
  TLorentzVector jet1(dvalue,dvalue,dvalue,dvalue);
  if (njet>=1) jet1 = vecjet.at(0)->p4();
  TLorentzVector jet2(dvalue,dvalue,dvalue,dvalue);
  if (njet>=2) jet2 = vecjet.at(1)->p4();
  TLorentzVector muon1(dvalue,dvalue,dvalue,dvalue);
  if (nmuon>=1) muon1 = vecmuon.at(0)->p4();
  TLorentzVector muon2(dvalue,dvalue,dvalue,dvalue);
  if (nmuon>=2) muon2 = vecmuon.at(1)->p4();
  TLorentzVector muon3(dvalue,dvalue,dvalue,dvalue);
  if (nmuon>=3) muon3 = vecmuon.at(2)->p4();
  TLorentzVector ele1(dvalue,dvalue,dvalue,dvalue);
  if (nele>=1) ele1 = vecele.at(0)->p4();
  TLorentzVector ele2(dvalue,dvalue,dvalue,dvalue);
  if (nele>=2) ele2 = vecele.at(1)->p4();
  TLorentzVector lep1(dvalue,dvalue,dvalue,dvalue);
  if (nlep>=1) lep1 = veclep.at(0)->p4();
  TLorentzVector ep(dvalue,dvalue,dvalue,dvalue);
  if (nele_p>=1) ep = vecele_p.at(0)->p4();
  TLorentzVector em(dvalue,dvalue,dvalue,dvalue);
  if (nele_m>=1) em = vecele_m.at(0)->p4();
  TLorentzVector up1(dvalue,dvalue,dvalue,dvalue);
  if (nmuon_p>=1) up1 = vecmuon_p.at(0)->p4();
  TLorentzVector up2(dvalue,dvalue,dvalue,dvalue);
  if (nmuon_p>=2) up2 = vecmuon_p.at(1)->p4();
  TLorentzVector um1(dvalue,dvalue,dvalue,dvalue);
  if (nmuon_m>=1) um1 = vecmuon_m.at(0)->p4();
  TLorentzVector um2(dvalue,dvalue,dvalue,dvalue);
  if (nmuon_m>=2) um2 = vecmuon_m.at(1)->p4();
  TLorentzVector muon_uniChar(dvalue,dvalue,dvalue,dvalue);
  if (nmuon_p==2 && nmuon_m==1) muon_uniChar = up2;
  if (nmuon_m==2 && nmuon_p==1) muon_uniChar = um2;

  DEBUGclass("nmuon:%i nele:%i njet:%i",nmuon,nele,njet);
  
  float Zmass = 91187.6; // MeV
  TLorentzVector up_method2(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector um_method2(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector muon3_method2(dvalue,dvalue,dvalue,dvalue);
  if (nmuon_p==2 && nmuon_m==1) {
    float M_up1um1 = (up1+um1).M();
    float M_up2um1 = (up2+um1).M();
    if (abs(M_up1um1-Zmass)>=abs(M_up2um1-Zmass)) {muon3_method2 = up1; up_method2=up2; um_method2=um1;}
    if (abs(M_up1um1-Zmass)<=abs(M_up2um1-Zmass)) {muon3_method2 = up2; up_method2=up1; um_method2=um1;}
  }
  if (nmuon_p==1 && nmuon_m==2) {
    float M_up1um1 = (up1+um1).M();
    float M_up1um2 = (up1+um2).M();
    if (abs(M_up1um1-Zmass)>=abs(M_up1um2-Zmass)) {muon3_method2 = um1; up_method2=up1; um_method2=um2;}
    if (abs(M_up1um1-Zmass)<=abs(M_up1um2-Zmass)) {muon3_method2 = um2; up_method2=up1; um_method2=um1;}
  }
  DEBUGclass("up_method2 pt:%f um_method2 pt:%f muon3_method2 pt:%f",up_method2.Pt(),um_method2.Pt(),muon3_method2.Pt());
  
  TLorentzVector up(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector um(dvalue,dvalue,dvalue,dvalue);
  TLorentzVector u3(dvalue,dvalue,dvalue,dvalue);

  int n_match=0;
  if(nmuon==3 && nmuon_p>=1 && nmuon_m>=1) {
    for (int i = 0; i < njet; ++i){
      auto jet = vecjet.at(i)->p4();
      if(jet.DeltaR(muon_uniChar)<1) n_match++;
    }
    if(n_match==1){up=up1; um=um1; u3=muon_uniChar;}
    else {up=up_method2; um=um_method2; u3=muon3_method2;}
  }
  DEBUGclass("up pt:%f um pt:%f u3 pt:%f",up.Pt(),um.Pt(),u3.Pt());
  
  DEBUGclass("============================ event info end =====================");
  //number
  myvector.push_back(njet);
  myvector.push_back(nSRjet);
  myvector.push_back(nmuon);
  myvector.push_back(nele);
  myvector.push_back(nmuon_p);
  myvector.push_back(nmuon_m);
  myvector.push_back(nele_p);
  myvector.push_back(nele_m);//7

  myvector.push_back(miss.Phi());
  myvector.push_back(miss.E()/1000);//9
      
  myvector.push_back(jet1.Pt()/1000);
  myvector.push_back(jet1.Eta());
  myvector.push_back(jet1.Phi());
  myvector.push_back(jet1.E()/1000);
  myvector.push_back(jet1.M()/1000);//14
  DEBUGclass("jet1 px:%f jet1 py:%f jet1 pz:%f jet1 e:%f jet1 m:%f",jet1.Px()/1000,jet1.Py()/1000,jet1.Pz()/1000,jet1.E()/1000,jet1.M()/1000);
  
  myvector.push_back(jet2.Pt()/1000);
  myvector.push_back(jet2.Eta());
  myvector.push_back(jet2.Phi());
  myvector.push_back(jet2.E()/1000);
  myvector.push_back(jet2.M()/1000);//19

  myvector.push_back(muon1.Pt()/1000);
  myvector.push_back(muon1.Eta());
  myvector.push_back(muon1.Phi());
  myvector.push_back(muon1.E()/1000);
  myvector.push_back(muon1.M()/1000);//24

  myvector.push_back(muon2.Pt()/1000);
  myvector.push_back(muon2.Eta());
  myvector.push_back(muon2.Phi());
  myvector.push_back(muon2.E()/1000);
  myvector.push_back(muon2.M()/1000);//29

  myvector.push_back(ele1.Pt()/1000);
  myvector.push_back(ele1.Eta());
  myvector.push_back(ele1.Phi());
  myvector.push_back(ele1.E()/1000);
  myvector.push_back(ele1.M()/1000);//34

  myvector.push_back(up.Pt()/1000);
  myvector.push_back(up.Eta());
  myvector.push_back(up.Phi());
  myvector.push_back(up.E()/1000);
  myvector.push_back(up.M()/1000);//39

  myvector.push_back(um.Pt()/1000);
  myvector.push_back(um.Eta());
  myvector.push_back(um.Phi());
  myvector.push_back(um.E()/1000);
  myvector.push_back(um.M()/1000);//44

  myvector.push_back(u3.Pt()/1000);
  myvector.push_back(u3.Eta());
  myvector.push_back(u3.Phi());
  myvector.push_back(u3.E()/1000);
  myvector.push_back(u3.M()/1000);//49

  myvector.push_back(ep.Pt()/1000);
  myvector.push_back(ep.Eta());
  myvector.push_back(ep.Phi());
  myvector.push_back(ep.E()/1000);
  myvector.push_back(ep.M()/1000);//54
  DEBUGclass("ep px:%f ep py:%f ep pz:%f ep e:%f ep m:%f",ep.Px()/1000,ep.Py()/1000,ep.Pz()/1000,ep.E()/1000,ep.M()/1000);
  myvector.push_back(em.Pt()/1000);
  myvector.push_back(em.Eta());
  myvector.push_back(em.Phi());
  myvector.push_back(em.E()/1000);
  myvector.push_back(em.M()/1000);//59
  DEBUGclass("em px:%f em py:%f em pz:%f em e:%f em m:%f",em.Px()/1000,em.Py()/1000,em.Pz()/1000,em.E()/1000,em.M()/1000);

  myvector.push_back(lep1.Pt()/1000);

  myvector.push_back(sumPt_SRjet/1000);//61

  myvector.push_back(muon1.DeltaR(muon2));
  myvector.push_back(muon1.DeltaR(ele1));
  myvector.push_back(jet1.DeltaR(muon1));
  myvector.push_back(jet1.DeltaR(muon2));
  myvector.push_back(jet1.DeltaR(ele1));//66

  myvector.push_back(muon1.DeltaR(ep));
  myvector.push_back(muon1.DeltaR(em));
  myvector.push_back(ep.DeltaR(em));
  myvector.push_back(jet1.DeltaR(ep));
  myvector.push_back(jet1.DeltaR(em));//71

  myvector.push_back(u3.DeltaR(up));
  myvector.push_back(u3.DeltaR(um));
  myvector.push_back(up.DeltaR(um));
  myvector.push_back(jet1.DeltaR(up));
  myvector.push_back(jet1.DeltaR(um));
  myvector.push_back(jet1.DeltaR(u3));//77

  myvector.push_back((jet1+muon1).M()/1000);
  myvector.push_back((jet1+muon1).Pt()/1000);
  myvector.push_back((jet1+muon2).M()/1000);
  myvector.push_back((jet1+muon2).Pt()/1000);//81

  myvector.push_back((ep+em).M()/1000);
  myvector.push_back((ep+em).Pt()/1000);
  myvector.push_back(get_mT(muon1,miss)/1000);
  myvector.push_back((muon1+miss).Pt()/1000);
  myvector.push_back(get_mT(muon1+jet1,miss)/1000);
  myvector.push_back((muon1+jet1+miss).Pt()/1000);//87

  myvector.push_back((up+um).M()/1000);
  myvector.push_back((up+um).Pt()/1000);
  myvector.push_back(get_mT(u3,miss)/1000);
  myvector.push_back((u3+miss).Pt()/1000);
  myvector.push_back(get_mT(u3+jet1,miss)/1000);
  myvector.push_back((u3+jet1+miss).Pt()/1000);//93

  int u1_charge=0;
  if (nmuon>=1) u1_charge = vecmuon.at(0)->charge();
  myvector.push_back(u1_charge);

  int u2_charge=0;
  if (nmuon>=2) u2_charge = vecmuon.at(1)->charge();
  myvector.push_back(u2_charge);

  int e1_charge=0;
  if (nele>=1) e1_charge = vecele.at(0)->charge();
  myvector.push_back(e1_charge);
  
  DEBUGclass("high level push suss");
  
  // bookmark cached entry
  this->fCachedEntry = this->getCurrentEntry();
  DEBUGclass("Created new set of cached values in instance '%s'",this->GetName());
  return true;
#endif
}

//______________________________________________________________________________________________

const std::vector<double>* ZHCand::getVector() const {
  // Function to retrieve the cached vector
  /* example block
     return &myvector;
  */
  
     return &myvector;
  //this should never be executed, we just make the compiler calm down
  throw std::runtime_error("Illegal / unsupported mode selected!");
  return NULL;
}

//______________________________________________________________________________________________

double ZHCand::getValue() const {
  // Value retrieval function, called on every event for every cut and histogram
  // Since this is a vector observable this should never be executed
  DEBUGclass("entering function getValue");
  throw std::runtime_error("Caught attempt to evaluate vector valued observable in scalar context");
  return std::numeric_limits<double>::quiet_NaN();
}

//______________________________________________________________________________________________

double ZHCand::getValueAt(int index) const {
  // Function to return element of vector with specified index
  if (!this->makeCache()) {
    ERROR("Failed to obtain return values!");
    return std::numeric_limits<double>::quiet_NaN();
  }

  const std::vector<double>* vec = this->getVector();
  if ((int)vec->size() == 0) { // vector is empty, not even filled once
    throw std::runtime_error("Attempted to retrieve value of vector that is empty");
    return std::numeric_limits<double>::quiet_NaN(); 
  }
  if (index >= (int)vec->size()) {
    throw std::runtime_error("Attempted to retrieve value for out of bounds");
    return std::numeric_limits<double>::quiet_NaN();
  }
  return vec->at(index);
}

//______________________________________________________________________________________________

int ZHCand::getNevaluations() const {
  // Function to return the size of the vector that is going to be retrieved
  
  if (!this->makeCache()) {
    ERROR("Failed to obtain return values!");
    return -1;
  }
  if (this->fType==TQObservable::ObservableType::scalar) return 1;
  const std::vector<double>* vec = this->getVector();
  if (vec) return vec->size();
  return -1;
}
//______________________________________________________________________________________________

bool ZHCand::initializeSelf(){
  // initialize this observable
  // called once per sample (input file) so that the observable knows the name of the event candidate
  // will be EventEM or EventME in the case of DF analysis (depending on the current channel)
  // example block
     TString ContName = "";
     if(!this->fSample->getTagString("~cand",ContName)) return false;
     this->mContName = "Event"+ContName;
  

  DEBUGclass("initializing");
  
  fCachedEntry = -1;
  return true;
}

//______________________________________________________________________________________________

bool ZHCand::finalizeSelf(){
  // finalize this observable
  // remember to undo anything you did in initializeSelf() !
  /* example block
     myvector.clear();
  */
  
  myvector.clear();
  DEBUGclass("finalizing");
  return true;
}
//______________________________________________________________________________________________

ZHCand::ZHCand(const TString& name):
TQEventObservable(name)
{
  // constructor with name argument
  DEBUGclass("constructor called with '%s'",name.Data());
}

bool ZHCand :: cmp_pt_IParticle (const xAOD::IParticle* a,const xAOD::IParticle* b)
{
    return a->pt() > b->pt();
}
bool ZHCand :: cmp_pt_Muon (const xAOD::Muon* a,const xAOD::Muon* b)
{
    return a->pt() > b->pt();
}
bool ZHCand :: cmp_pt_Electron (const xAOD::Electron* a,const xAOD::Electron* b)
{
    return a->pt() > b->pt();
}
bool ZHCand :: cmp_pt_TLorentzVector (TLorentzVector a,TLorentzVector b)
{
    return a.Pt() > b.Pt();
}
bool ZHCand :: cmp_pt_Jet (const xAOD::Jet* a,const xAOD::Jet* b)
{
    return a->pt() > b->pt();
}




    
