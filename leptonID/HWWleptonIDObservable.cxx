#include "HWWAnalysisCode/HWWLeptonIDObservable.h"
#include <limits>
// uncomment the following line to enable debug printouts
#define _DEBUG_
// you can perform debug printouts with statements like this
// DEBUG("error number %d occurred",someInteger);
// be careful to not move the _DEBUG_ flag behind the following line
// otherwise, it will show no effect
#include "QFramework/TQLibrary.h"
ClassImp(HWWLeptonIDObservable)

//______________________________________________________________________________________________
HWWLeptonIDObservable::HWWLeptonIDObservable() :
fIndexLeadLep(0),
fIndexSubleadLep(1),
fIndexThirdLep(2),
fIndexFourthLep(3),
fIndexOtherLep(0)
{
  // default constructor
  DEBUGclass("default constructor called");
}
//______________________________________________________________________________________________
// copy constructor
HWWLeptonIDObservable::HWWLeptonIDObservable(const HWWLeptonIDObservable& obs) :
// LeptonIDHelper for anti-id and id selections
  TQEventObservable(obs),
  fLeptonIDHelper(new HWW::HWWLeptonIDHelper(*obs.fLeptonIDHelper)),
  fHWWLepIDModeOfRunning(obs.fHWWLepIDModeOfRunning),
  fHWWAnalysisType(obs.fHWWAnalysisType),
  fIndexLeadLep(obs.fIndexLeadLep),
  fIndexSubleadLep(obs.fIndexSubleadLep),
  fIndexThirdLep(obs.fIndexThirdLep),
  fIndexFourthLep(obs.fIndexFourthLep),
  fIndexOtherLep(obs.fIndexOtherLep),
  mCand(obs.mCand),
  mCandName(obs.mCandName) {

  DEBUGclass("Inside copy constructor");
  // check that a valid value was given
  switch (fHWWLepIDModeOfRunning) {
    case HWWLepIDModeOfRunning::LeadLepID:
      break;
    case HWWLepIDModeOfRunning::SubleadLepID:
      break;
    case HWWLepIDModeOfRunning::ThirdLepID:
      break;
    case HWWLepIDModeOfRunning::lvqqSubleadLepID:
      break;
    case HWWLepIDModeOfRunning::lvqqThirdLepID:
      break;
    case HWWLepIDModeOfRunning::FourthLepID:
      break;
    case HWWLepIDModeOfRunning::OtherLepID:
      break;
    case HWWLepIDModeOfRunning::LeadLepAntiID:
      break;
    case HWWLepIDModeOfRunning::SubleadLepAntiID:
      break;
    case HWWLepIDModeOfRunning::ThirdLepAntiID:
      break;
    case HWWLepIDModeOfRunning::FourthLepAntiID:
      break;
    case HWWLepIDModeOfRunning::OtherLepAntiID:
      break;
    case HWWLepIDModeOfRunning::Muon1ID:
      break;
    case HWWLepIDModeOfRunning::Muon2ID:
      break;
    case HWWLepIDModeOfRunning::Muon3ID:
      break;
    case HWWLepIDModeOfRunning::Ele1ID:
      break;
    case HWWLepIDModeOfRunning::Ele2ID:
      break;
    case HWWLepIDModeOfRunning::Lep1ID:
      break;
    case HWWLepIDModeOfRunning::Lep2ID:
      break;
    default:
      throw std::runtime_error("[HWWLeptonIDObservable] Invalid mode-of-running value given!");
  }
  switch (fHWWAnalysisType) {
    case HWWAnalysisType::TwoLep:
      break;
    case HWWAnalysisType::WH:
      break;
    case HWWAnalysisType::ZH:
      break;
    case HWWAnalysisType::OneLep:
      break;
    default:
      throw std::runtime_error("ERROR in HWWLeptonIDObservable :: Unknown analysis type given!");
  }
  if (!fLeptonIDHelper) { throw std::runtime_error("ERROR in HWWLeptonIDObservable :: you must pass a valid pointer to your HWWLeptonIDHelper object!"); }

  DEBUGclass("Running with mode of running: %d", fHWWLepIDModeOfRunning);
  DEBUGclass("Running with anlysis type: %d:", fHWWAnalysisType);
}

//______________________________________________________________________________________________
HWWLeptonIDObservable::~HWWLeptonIDObservable(){
  // default destructor
  DEBUGclass("destructor called");
}
#define XAOD_STANDALONE 1
// put here any EDM includes you might need, e.g.
//#include "xAODParticleEvent/CompositeParticleContainer.h"
//______________________________________________________________________________________________
double HWWLeptonIDObservable::getValue() const {
  // value retrieval function, called on every event for every cut and histogram
  DEBUGclass("entering function");
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
  // first, you can retrieve the data members you needwith the 'retrieve' method
  // as arguments to this function, pass the member pointer to the container as well as the container name
  /* example block:
  xAOD::CompositeParticleContainer* cont = NULL;
  this->retrieve(cont, "EECands");
  */
  // after you have retrieved your data members, you can proceed to calculate the return value
  // probably, you first have to retrieve an element from the container
  /* example block:
  const CompositeParticle* p = cont->at(0);
  */
  // in the end, you should calculate your return value
  // of course, you can use other data members of your observable at any time
  /* exmple block:
  const double retval = p->electron(0)->passSelection(this->fExpression.Data());
  */
  if(!this->fEvent->retrieve(this->mCand, this->mCandName.Data()).isSuccess()){
    DEBUGclass("failed to retrieve candidates!");
    return 0;
  }
  // DEBUGclass("retrieve candidates! %s",this->mCandName.Data());
  const xAOD::CompositeParticle *Evt = this->mCand->at(0);
  // DEBUGclass(" this->mCand->size() %i",this->mCand->size());

  if(this->mCand->size()==0) return 0.;
  // lepton of interest
  const xAOD::IParticle* lepOfInterest = nullptr;
  // get it from event candidate depending on mode of running



    
//1st loop
  DEBUGclass("============================ lepIDObservable info start ===============================");
  std::vector<const xAOD::IParticle*> vecmuon;
  std::vector<const xAOD::IParticle*> vecele;
  std::vector<const xAOD::IParticle*> veclep;
    
//1st loop
  DEBUGclass("============================ event info start ===============================");
  for (std::size_t n = 0; n < Evt->nParts(); ++n){
    if (Evt->part(n)->type()==xAOD::Type::Muon){
      const xAOD::IParticle *muon = Evt->muon(n);
      vecmuon.push_back(muon);
      veclep.push_back(muon);
    }
    if (Evt->part(n)->type()==xAOD::Type::Electron){
      const xAOD::IParticle* ele=Evt->electron(n);
      vecele.push_back(ele);
      veclep.push_back(ele);
    }    
  }
  for (std::size_t n = 0; n < Evt->nOtherParts(); ++n){
    if (Evt->otherPart(n)->type()==xAOD::Type::Muon){
      const xAOD::IParticle *muon = Evt->otherMuon(n);
      vecmuon.push_back(muon);
      veclep.push_back(muon);
    }
    if (Evt->otherPart(n)->type()==xAOD::Type::Electron){
      const xAOD::IParticle* ele=Evt->otherElectron(n);
      vecele.push_back(ele);
      veclep.push_back(ele);
    }    
  }
  DEBUGclass("retrive lep done");
  
  int nmuon=vecmuon.size();
  int nele=vecele.size();
  int nlep=veclep.size();
  DEBUGclass("number lep done");
  
  std::sort(veclep.begin(), veclep.end(), cmp_pt_IParticle );
  std::sort(vecmuon.begin(), vecmuon.end(), cmp_pt_IParticle );
  std::sort(vecele.begin(), vecele.end(), cmp_pt_IParticle );
  DEBUGclass("sort done");

  const xAOD::IParticle* muon1;
  if (nmuon>=1) muon1 = vecmuon.at(0);
  const xAOD::IParticle* muon2;
  if (nmuon>=2) muon2 = vecmuon.at(1);
  const xAOD::IParticle* muon3;
  if (nmuon>=3) muon3 = vecmuon.at(2);
  const xAOD::IParticle* ele1;
  if (nele>=1) ele1 = vecele.at(0);
  const xAOD::IParticle* ele2;
  if (nele>=2) ele2 = vecele.at(1);
  const xAOD::IParticle* lep1;
  if (nlep>=1) lep1 = veclep.at(0);
  const xAOD::IParticle* lep2;
  if (nlep>=2) lep2 = veclep.at(1);
  DEBUGclass("set lep done");
  
  
  

  DEBUGclass("(HWWLepIDModeOfRunning) Retrieving candidate for %d", fHWWLepIDModeOfRunning);
  switch (fHWWLepIDModeOfRunning) {
    // leading lepton
    case HWWLepIDModeOfRunning::LeadLepID: case HWWLepIDModeOfRunning::LeadLepAntiID:
        DEBUGclass("LeadLepID");
        lepOfInterest = Evt->part(fIndexLeadLep);
        break;
    // subleading lepton
    case HWWLepIDModeOfRunning::SubleadLepID: case HWWLepIDModeOfRunning::SubleadLepAntiID:
        switch (fHWWAnalysisType) {
            case HWWAnalysisType::TwoLep: case HWWAnalysisType::WH: case HWWAnalysisType::ZH:
                DEBUGclass("for 2nd lep other %d", fIndexOtherLep );
                lepOfInterest = Evt->part(fIndexSubleadLep);
                //for lvqqtest
                //lepOfInterest = Evt->otherPart(fIndexOtherLep);
                break;
            default:
                throw std::runtime_error("ERROR in HWWLeptonIDObservable :: HWWAnalysisType::OneLepton should not be trying to access second lepton mode of running.");
        }
        // BREAK
        break;
    //lvqq vh subleading lepton
    case HWWLepIDModeOfRunning::lvqqSubleadLepID: 
        switch (fHWWAnalysisType) {
            case HWWAnalysisType::TwoLep: case HWWAnalysisType::WH: case HWWAnalysisType::ZH:
                DEBUGclass("for lvqq 2nd lep other 0");
                lepOfInterest = Evt->otherPart(0);
                break;
            default:
                throw std::runtime_error("ERROR in HWWLeptonIDObservable :: lvqqSubleadLepID");
        }
        // BREAK
        break;
    // third lepton (for VH)
    case HWWLepIDModeOfRunning::ThirdLepID: case HWWLepIDModeOfRunning::ThirdLepAntiID:
        switch (fHWWAnalysisType) {
            case HWWAnalysisType::WH: case HWWAnalysisType::ZH:
                //DEBUGclass("3rd lep");
                lepOfInterest = Evt->part(fIndexThirdLep);
                //lvqq test
                //DEBUGclass("3rd lep other");
                //lepOfInterest = Evt->otherPart(1);
                break;
            default:
                throw std::runtime_error("ERROR in HWWLeptonIDObservable :: HWWAnalysisType::OneLepton or HWWAnalysisType::TwoLepton should not be trying to access third lepton mode of running.");
        }
        // BREAK
        break;
    // third lepton (for VH lvqq)
    case HWWLepIDModeOfRunning::lvqqThirdLepID: 
        switch (fHWWAnalysisType) {
            case HWWAnalysisType::WH: case HWWAnalysisType::ZH:
                DEBUGclass("lvqq 3rd lep other 1");
                lepOfInterest = Evt->otherPart(1);
                break;
            default:
                throw std::runtime_error("ERROR in HWWLeptonIDObservable :: lvqqThirdLepID");
        }
        // BREAK
        break;
    // fourth lepton (for ZH)
    case HWWLepIDModeOfRunning::FourthLepID: case HWWLepIDModeOfRunning::FourthLepAntiID:
        switch (fHWWAnalysisType) {
            case HWWAnalysisType::ZH:
                //DEBUGclass("4th lep");
                lepOfInterest = Evt->part(fIndexFourthLep);
                break;
            default:
                throw std::runtime_error("ERROR in HWWLeptonIDObservable :: HWWAnalysisType::OneLepton or HWWAnalysisType::TwoLepton or HWWAnalysisType::WH should not be trying to access fourth lepton mode of running.");
        }
        // BREAK
        break;
    // other lepton (for 2L)
    case HWWLepIDModeOfRunning::OtherLepID: case HWWLepIDModeOfRunning::OtherLepAntiID:
        //switch (fHWWAnalysisType) {
        //    case HWWAnalysisType::TwoLep:
                //DEBUGclass("other lep");
                lepOfInterest = Evt->otherPart(fIndexOtherLep);
                if (!lepOfInterest) return 0; //let's just graciously say a non-existent particle is neither ID nor AntiID
         //       break;
         //   default:
         //       throw std::runtime_error("ERROR in HWWLeptonIDObservable :: Other lepton mode of running is currently restricted to HWWAnalysisType::TwoLepton -- does this make sense?");
        //}
        // BREAK
        break;
    
    // muon1 (for ZH)
    case HWWLepIDModeOfRunning::Muon1ID:
        DEBUGclass("muon1 id");
        lepOfInterest = muon1;
        break;

    case HWWLepIDModeOfRunning::Muon2ID:
        DEBUGclass("muon2 id");
        lepOfInterest = muon2;
        break;

    case HWWLepIDModeOfRunning::Muon3ID:
        DEBUGclass("muon3 id");
        lepOfInterest = muon3;
        break;

    case HWWLepIDModeOfRunning::Ele1ID:
        DEBUGclass("ele1 id");
        lepOfInterest = ele1;
        break;

    case HWWLepIDModeOfRunning::Ele2ID:
        DEBUGclass("ele2 id");
        lepOfInterest = ele2;
        break;

    case HWWLepIDModeOfRunning::Lep1ID:
        DEBUGclass("lep1 id");
        lepOfInterest = lep1;
        break;

    case HWWLepIDModeOfRunning::Lep2ID:
        DEBUGclass("lep2 id");
        lepOfInterest = lep2;
        break;
    
    default:
        DEBUGclass("In event retrieval error.");
        throw std::runtime_error("ERROR in HWWLeptonIDObservable :: unrecognised mode of running. Check your configuration of this observable.");
  }
  
  // check that particle exists
  if (!lepOfInterest) throw std::runtime_error("[HWWLeptonIDObservable] failed to retrieve iParticle!");

  //if it's not a lepton it's neither ID not AntiID
  if (! (lepOfInterest->type() == 6 || lepOfInterest->type () == 8) ) return 0;
  // compute pass or fail
  bool pass(false);
  switch (fHWWLepIDModeOfRunning) {
    // id
    case HWWLepIDModeOfRunning::LeadLepID: case HWWLepIDModeOfRunning::SubleadLepID: case HWWLepIDModeOfRunning::ThirdLepID: case HWWLepIDModeOfRunning::lvqqSubleadLepID: case HWWLepIDModeOfRunning::lvqqThirdLepID: case HWWLepIDModeOfRunning::FourthLepID: case HWWLepIDModeOfRunning::OtherLepID: case HWWLepIDModeOfRunning::Muon1ID: case HWWLepIDModeOfRunning::Muon2ID: case HWWLepIDModeOfRunning::Muon3ID: case HWWLepIDModeOfRunning::Ele1ID: case HWWLepIDModeOfRunning::Ele2ID: case HWWLepIDModeOfRunning::Lep1ID: case HWWLepIDModeOfRunning::Lep2ID:
        pass = fLeptonIDHelper->isID(lepOfInterest);
        break;
    // anti-id
    case HWWLepIDModeOfRunning::LeadLepAntiID: case HWWLepIDModeOfRunning::SubleadLepAntiID: case HWWLepIDModeOfRunning::ThirdLepAntiID: case HWWLepIDModeOfRunning::FourthLepAntiID: case HWWLepIDModeOfRunning::OtherLepAntiID:
        pass = fLeptonIDHelper->isAntiID(lepOfInterest);
        break;
    default:
        DEBUGclass("In event cut error.");
        throw std::runtime_error("ERROR in HWWLeptonIDObservable :: unrecognised mode of running. Check your configuration of this observable.");
  }
  DEBUGclass("--------------------returning: %d -----------------------------", pass);
  return static_cast<double>(pass);
  #endif
}
//______________________________________________________________________________________________
// getClone override (so we don't have to rely on root streamer)
TQObservable* HWWLeptonIDObservable::getClone() const  {
  // retrieve a clone of this observable
  TQObservable* obs = NULL;
  if(this->hasExpression()){
    obs = this->tryCreateInstanceVirtual(this->getExpression());
  }
  if(!obs){
    // obs = (TQObservable*)(this->Clone()); DON'T USE ROOT STREAMER, INSTEAD USE COPY constructor
    obs = new HWWLeptonIDObservable(*this);
  }
  if(obs->isInitialized()) obs->finalize();
  return obs;
}

//______________________________________________________________________________________________
bool HWWLeptonIDObservable::initializeSelf(){
  TString CandName = "";
  if(!this->fSample->getTagString("~cand",CandName)) return false;
  //The following is needed in combination with (e.g.) the WHMuonPtCorrectionAlgorithm.
  // The algorithm adds a modified EventCand ("EventCorrWH", possibly with additional systematics suffix) with slightly modified kinematics
  // For the determination of ID/antiID we must use the original kinematics though (the correction itself depends on an object being ID/antiID)
  // -> remove the "Corr" prefix from the cand name here (doesn't affect anyone else)
  TQStringUtils::removeLeadingText(CandName,"Corr"); 
  this->mCandName = "Event"+CandName;
  return true;
}
//______________________________________________________________________________________________
HWWLeptonIDObservable::HWWLeptonIDObservable(const TString& name, const HWW::HWWLeptonIDHelper* lepIDHelper,
                                    const int mode_of_running, const int analysis_type,
                                    const unsigned int indexLeadLep, const unsigned int indexSubleadLep,
                                    const unsigned int indexThirdLep, const unsigned int indexFourthLep,
                                    const unsigned int indexOtherLep):
  TQEventObservable(name),
  fLeptonIDHelper(lepIDHelper),
  fIndexLeadLep(indexLeadLep),
  fIndexSubleadLep(indexSubleadLep),
  fIndexThirdLep(indexThirdLep),
  fIndexFourthLep(indexFourthLep),
  fIndexOtherLep(indexOtherLep)
{
  // constructor with name argument
  DEBUGclass("constructor called with '%s'",name.Data());
  fHWWLepIDModeOfRunning = static_cast<HWWLepIDModeOfRunning>(mode_of_running);
  fHWWAnalysisType = static_cast<HWWAnalysisType>(analysis_type);
  // check that a valid value was given
  switch (fHWWLepIDModeOfRunning) {
    case HWWLepIDModeOfRunning::LeadLepID:
      break;
    case HWWLepIDModeOfRunning::SubleadLepID:
      break;
    case HWWLepIDModeOfRunning::ThirdLepID:
      break;
    case HWWLepIDModeOfRunning::lvqqSubleadLepID:
      break;
    case HWWLepIDModeOfRunning::lvqqThirdLepID:
      break;
    case HWWLepIDModeOfRunning::FourthLepID:
      break;
    case HWWLepIDModeOfRunning::OtherLepID:
      break;
    case HWWLepIDModeOfRunning::LeadLepAntiID:
      break;
    case HWWLepIDModeOfRunning::SubleadLepAntiID:
      break;
    case HWWLepIDModeOfRunning::ThirdLepAntiID:
      break;
    case HWWLepIDModeOfRunning::FourthLepAntiID:
      break;
    case HWWLepIDModeOfRunning::OtherLepAntiID:
      break;
    case HWWLepIDModeOfRunning::Muon1ID:
      break;
    case HWWLepIDModeOfRunning::Muon2ID:
      break;
    case HWWLepIDModeOfRunning::Muon3ID:
      break;
    case HWWLepIDModeOfRunning::Ele1ID:
      break;
    case HWWLepIDModeOfRunning::Ele2ID:
      break;
    case HWWLepIDModeOfRunning::Lep1ID:
      break;
    case HWWLepIDModeOfRunning::Lep2ID:
      break;
    
    default:
      throw std::runtime_error("[HWWLeptonIDObservable] Invalid mode-of-running value given!");
  }
  switch (fHWWAnalysisType) {
    case HWWAnalysisType::TwoLep:
      break;
    case HWWAnalysisType::WH:
      break;
    case HWWAnalysisType::ZH:
      break;
    case HWWAnalysisType::OneLep:
      break;
    default:
      throw std::runtime_error("ERROR in HWWLeptonIDObservable :: Unknown analysis type given!");
  }
  if (!fLeptonIDHelper) { throw std::runtime_error("ERROR in HWWLeptonIDObservable :: you must pass a valid pointer to your HWWLeptonIDHelper object!"); }

  DEBUGclass("Running with mode %d", fHWWLepIDModeOfRunning);
  DEBUGclass("Running with analysis type %d", fHWWAnalysisType);
}

bool HWWLeptonIDObservable :: cmp_pt_IParticle (const xAOD::IParticle* a,const xAOD::IParticle* b)
{
    return a->pt() > b->pt();
}
bool HWWLeptonIDObservable :: cmp_pt_Muon (const xAOD::Muon* a,const xAOD::Muon* b)
{
    return a->pt() > b->pt();
}
bool HWWLeptonIDObservable :: cmp_pt_Electron (const xAOD::Electron* a,const xAOD::Electron* b)
{
    return a->pt() > b->pt();
}
