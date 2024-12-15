#include "HWWAnalysisCode/HWWTrigBase.h"

// Uncomment the following line to enable debug printouts
#define _DEBUG_
using namespace std;
#include "QFramework/TQLibrary.h"

//______________________________________________________________________________________________
// constructor
HWWTrigBase::HWWTrigBase(const std::vector<HWWTrigConfig*>& trigConfigs):
  HWWTrigBase()
{
  for(const auto& t:trigConfigs){
    this->addTriggerConfig(t);
  }
}

//______________________________________________________________________________________________
// constructor
HWWTrigBase::HWWTrigBase():
  m_trigpass_prefix("pass_"),
  m_trigmatch_prefix("trigMatch_")
{
	DEBUGclass("constructor of HWWTrigBase");
}

//______________________________________________________________________________________________
void HWWTrigBase::addTriggerConfig(HWWTrigConfig* trigConfig){
  this->m_trigConfigs.push_back(trigConfig);
}

//______________________________________________________________________________________________
// destructor
HWWTrigBase::~HWWTrigBase() {

}

//______________________________________________________________________________________________
HWWTrigConfig* HWWTrigBase::getTrigConfig(const xAOD::EventInfo* evtInfo) const {
	unsigned int runNumber;
	if (evtInfo->isAvailable<unsigned int>("RandomRunNumber")){
    //if(evtinfo->eventType(xAOD::EventInfo::IS_SIMULATION)){
    runNumber = evtInfo->auxdata<unsigned int> ("RandomRunNumber");
  } else {
    runNumber = evtInfo->runNumber();
  }
  // find out based on run number which is the correct HWWTrigConf
  DEBUGclass(TString::Format("runNumber = %d", runNumber).Data());
	for (const auto& trigconf : m_trigConfigs) {
		if (runNumber >= trigconf->runNumberLow && runNumber <= trigconf->runNumberUp) {
			return trigconf;
		}
	}
	// should never end up here
	return nullptr;
}

//______________________________________________________________________________________________
bool HWWTrigBase::isMatchedAnySingleElParticle(const xAOD::IParticle* electron, const HWWTrigConfig* trigConf, const xAOD::EventInfo* evtInfo) const {
  // loop over triggers and return passed if offline electron matches any of them, and also passes pt cut
  const bool isMC = evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION);
  // loop over single electron triggers
  const std::vector<TString>& triggers = isMC ? trigConf->elecTrigsMC : trigConf->elecTrigsData;
  // check offline electron pT cut
  if (electron->pt() >= trigConf->elecPtCut) {
    for (unsigned int itrig(0); itrig < triggers.size(); ++itrig) {
      DEBUGclass(TString::Format("checking trigger %s", triggers[itrig].Data()).Data());
      if (isMatchedTriggerParticle(electron,triggers[itrig])) {
        DEBUGclass("matched to single electron trigger");
        return true;
      }
    }
  }
  return false;
}

//______________________________________________________________________________________________
// from-outside version of above function
bool HWWTrigBase::isMatchedAnySingleElParticle(const xAOD::IParticle* electron, const xAOD::EventInfo* evtInfo) const {
  // get trigConf...
  const HWWTrigConfig* trigConf = getTrigConfig(evtInfo);
  if (!trigConf) {
    // there seem to be events in MC with RandomRunNr = 0. Coming from mu not represented and thus having weight=0? Previous implementation must then have said false.
    if (evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) {
      if (evtInfo->auxdata<unsigned int>("RandomRunNumber") == 0) {
        // std::cout << "WARNING in HWWTrigBase :: RandomRunNumber == 0, interpreting as trigger miss." << std::endl;
        return false;
      }
    }
    throw std::runtime_error("In HWWTrigBase::isMatchedAnySingleElParticle :: invalid HWWTrigConfig pointer! Are you sure you passed the TrigConfig objects to your observable? Also check with what run numbers they are configured.");
  }
  // ... call private fcn
  return isMatchedAnySingleElParticle(electron, trigConf, evtInfo);
}

//______________________________________________________________________________________________
bool HWWTrigBase::isMatchedAnySingleMuParticle(const xAOD::IParticle* muon, const HWWTrigConfig* trigConf, const xAOD::EventInfo* evtInfo) const {
  // loop over triggers and return passed if offline muon matches any of them, and also passes pt cut
  const bool isMC = evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION);
  // loop over single muon triggers
  const std::vector<TString>& triggers = isMC ? trigConf->muonTrigsMC : trigConf->muonTrigsData;
  // check offline muon pT cut
  if (muon->pt() >= trigConf->muonPtCut) {
    for (unsigned int itrig(0); itrig < triggers.size(); itrig++) {
      DEBUGclass(TString::Format("checking trigger %s", triggers[itrig].Data()).Data());
      if (isMatchedTriggerParticle(muon,triggers[itrig])) {
        DEBUGclass("matched to single muon trigger");
        return true;
      }
    }
  }
  return false;
}
//______________________________________________________________________________________________
// from-outside version of above fcn.
bool HWWTrigBase::isMatchedAnySingleMuParticle(const xAOD::IParticle* muon, const xAOD::EventInfo* evtInfo) const {
  // get trigConf...
  const HWWTrigConfig* trigConf = getTrigConfig(evtInfo);
  if (!trigConf) {
    // there seem to be events in MC with RandomRunNr = 0. Coming from mu not represented and thus having weight=0? Previous implementation must then have said false.
    if (evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) {
      if (evtInfo->auxdata<unsigned int>("RandomRunNumber") == 0) {
        // std::cout << "WARNING in HWWTrigBase :: RandomRunNumber == 0, interpreting as trigger miss." << std::endl;
        return false;
      }
    }
    throw std::runtime_error("In HWWTrigBase::isMatchedAnySingleMuParticle :: invalid HWWTrigConfig pointer! Are you sure you passed the TrigConfig objects to your observable? Also check with what run numbers they are configured.");
  }
  // ... call private function
  return isMatchedAnySingleMuParticle(muon, trigConf, evtInfo);
}
//______________________________________________________________________________________________
bool HWWTrigBase::isMatchedAnyDiMuParticle(const xAOD::IParticle* muon, const HWWTrigConfig* trigConf, const xAOD::EventInfo* evtInfo) const {
  // loop over triggers and return passed if offline muon matches any of them, and also passes pt cut
  const bool isMC = evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION);
  // loop over single muon triggers
  const std::vector<TString>& triggers = isMC ? trigConf->dimuTrigsMC : trigConf->dimuTrigsData;
  // check offline muon pT cut
  if (muon->pt() >= trigConf->dimuPtCut) {
    for (unsigned int itrig(0); itrig < triggers.size(); itrig++) {
      DEBUGclass(TString::Format("checking trigger %s", triggers[itrig].Data()).Data());
      if (isMatchedTriggerParticle(muon,triggers[itrig])) {
        DEBUGclass("matched to di muon trigger");
        return true;
      }
    }
  }
  return false;
}
//______________________________________________________________________________________________
// from-outside version of above fcn.
bool HWWTrigBase::isMatchedAnyDiMuParticle(const xAOD::IParticle* muon, const xAOD::EventInfo* evtInfo) const {
  // get trigConf...
  const HWWTrigConfig* trigConf = getTrigConfig(evtInfo);
  if (!trigConf) {
    // there seem to be events in MC with RandomRunNr = 0. Coming from mu not represented and thus having weight=0? Previous implementation must then have said false.
    if (evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) {
      if (evtInfo->auxdata<unsigned int>("RandomRunNumber") == 0) {
        // std::cout << "WARNING in HWWTrigBase :: RandomRunNumber == 0, interpreting as trigger miss." << std::endl;
        return false;
      }
    }
    throw std::runtime_error("In HWWTrigBase::isMatchedAnySingleMuParticle :: invalid HWWTrigConfig pointer! Are you sure you passed the TrigConfig objects to your observable? Also check with what run numbers they are configured.");
  }
  // ... call private function
  return isMatchedAnyDiMuParticle(muon, trigConf, evtInfo);
}
//______________________________________________________________________________________________
bool HWWTrigBase::isMatchedTriggerParticle(const xAOD::IParticle* part, const TString& trigger) const {
  // trigmatch expression passed, simply match electron
//       TString trigger1="HLT_mu26_ivarmedium"; 
// TString trigger2="HLT_e26_lhtight_nod0_ivarloose"; 
// TString trigger1="HLT_mu18_mu8noL1"; 
// TString trigger2="HLT_2mu10";
// TString trigger3="HLT_mu20_mu8noL1"; 
// TString trigger4="HLT_mu22_mu8noL1"; 
// TString trigger5="HLT_2mu14"; 
// TString trigger6="HLT_mu22_mu8noL1_calotag_0eta010"; 
// auto bool1 = static_cast<bool>(part->auxdata<char>(std::string(m_trigmatch_prefix+trigger1.Data())));
// cout <<"bool1:"<<bool1<< endl;
// auto bool2 = static_cast<bool>(part->auxdata<char>(std::string(m_trigmatch_prefix+trigger2.Data())));
// cout <<"bool2:"<<bool2<< endl;
// auto bool3 = static_cast<bool>(part->auxdata<char>(std::string(m_trigmatch_prefix+trigger3.Data())));
// cout <<"bool3:"<<bool3<< endl;
// auto bool4 = static_cast<bool>(part->auxdata<char>(std::string(m_trigmatch_prefix+trigger4.Data())));
// cout <<"bool4:"<<bool4<< endl;
// auto bool5 = static_cast<bool>(part->auxdata<char>(std::string(m_trigmatch_prefix+trigger5.Data())));
// cout <<"bool5:"<<bool5<< endl;
// auto bool6 = static_cast<bool>(part->auxdata<char>(std::string(m_trigmatch_prefix+trigger6.Data())));
// cout <<"bool6:"<<bool6<< endl;
//   cout <<"trigger try match:"<<trigger.Data()<< endl;
  if (static_cast<bool>(part->auxdata<char>(std::string((m_trigmatch_prefix+trigger).Data())))) {
    // cout <<"pass"<< endl;
    DEBUGclass("is Matched Trigger Particle");
    return true;
  }
  // return static_cast<bool>(part->auxdata<char>(std::string((m_trigmatch_prefix+trigger).Data())));
  return false;
}

//______________________________________________________________________________________________
bool HWWTrigBase::isMatchedAnyDilepLegParticle(const xAOD::IParticle* part, const HWWTrigConfig* trigConf, const xAOD::EventInfo* evtInfo) const {
  // get dilepton trigger list for this event
  const std::vector<TString>& dilepTriggers = evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION) ? trigConf->dilepTrigsMC : trigConf->dilepTrigsData;
  unsigned int nDilepTriggers = dilepTriggers.size();
  // loop over triggers
  // TString trigger;
  for (unsigned int iDilep(0); iDilep < nDilepTriggers; iDilep++) {
    // Electron
    if (part->type() == xAOD::Type::Electron) {
      // the pt is event-level cut, check that first
      if (part->pt() > trigConf->dilepElLegPtCut) {
        if (isMatchedTriggerParticle(part, dilepTriggers[iDilep])) return true;
      }
    } else if (part->type() == xAOD::Type::Muon) {
      // the pt is event-level cut, check that first
      if (part->pt() > trigConf->dilepMuLegPtCut) {
        if (isMatchedTriggerParticle(part, dilepTriggers[iDilep])) return true;
      }
    }
  }
  return false;
}

//______________________________________________________________________________________________
// from-outside version of above function
bool HWWTrigBase::isMatchedAnyDilepLegParticle(const xAOD::IParticle* part, const xAOD::EventInfo* evtInfo) const {
  // get trigConf...
  const HWWTrigConfig* trigConf = getTrigConfig(evtInfo);
  if (!trigConf) {
    // there seem to be events in MC with RandomRunNr = 0. Coming from mu not represented and thus having weight=0? Previous implementation must then have said false.
    if (evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) {
      if (evtInfo->auxdata<unsigned int>("RandomRunNumber") == 0) {
        // std::cout << "WARNING in HWWTrigBase :: RandomRunNumber == 0, interpreting as trigger miss." << std::endl;
        return false;
      }
    }
    throw std::runtime_error("In HWWTrigBase::isMatchedAnyDilepLegParticle :: invalid HWWTrigConfig pointer! Are you sure you passed the TrigConfig objects to your observable? Also check with what run numbers they are configured.");
  }
  // ... call private fcn
  return isMatchedAnyDilepLegParticle(part, trigConf, evtInfo);
}

//______________________________________________________________________________________________
bool HWWTrigBase::isMatchedAnyParticle(const xAOD::IParticle* part, const HWWTrigConfig* trigConf, const xAOD::EventInfo* evtInfo) const {
  // is the particle matched to any of the triggers?
  // single muon
  if (part->type() == xAOD::Type::Muon && isMatchedAnySingleMuParticle(part, trigConf, evtInfo)) {
    return true;
  }
  // single electron
  if (part->type() == xAOD::Type::Electron && isMatchedAnySingleElParticle(part, trigConf, evtInfo)) {
    return true;
  }
  // dilepton triggers
  if (isMatchedAnyDilepLegParticle(part, trigConf, evtInfo)) {
    return true;
  }
  return false;
}

//______________________________________________________________________________________________
// called-from-outside version of above function
bool HWWTrigBase::isMatchedAnyParticle(const xAOD::IParticle* part, const xAOD::EventInfo* evtInfo) const {
  // get trigConf...
  const HWWTrigConfig* trigConf = getTrigConfig(evtInfo);
  if (!trigConf) {
    // there seem to be events in MC with RandomRunNr = 0. Coming from mu not represented and thus having weight=0? Previous implementation must then have said false.
    if (evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) {
      if (evtInfo->auxdata<unsigned int>("RandomRunNumber") == 0) {
        // std::cout << "WARNING in HWWTrigBase :: RandomRunNumber == 0, interpreting as trigger miss." << std::endl;
        return false;
      }
    }
    throw std::runtime_error("In HWWTrigBase::isMatchedAnyParticle :: invalid HWWTrigConfig pointer! Are you sure you passed the TrigConfig objects to your observable? Also check with what run numbers they are configured.");
  }
  // ...  call private function
  return isMatchedAnyParticle(part, trigConf, evtInfo);
}

//______________________________________________________________________________________________
bool HWWTrigBase::isPassedTrigger(const xAOD::EventInfo* evtInfo, const TString& trigger) const {
// TString trigger1="HLT_mu18_mu8noL1"; 
// TString trigger2="HLT_2mu10"; 
// TString trigger3="HLT_mu20_mu8noL1"; 
// TString trigger4="HLT_mu22_mu8noL1"; 
// TString trigger5="HLT_2mu14"; 
// TString trigger6="HLT_mu22_mu8noL1_calotag_0eta010"; 
// auto bool1 = static_cast<bool>(evtInfo->auxdata<char>(std::string(m_trigpass_prefix+trigger1.Data())));
// cout <<"bool1:"<<bool1<< endl;
// auto bool2 = static_cast<bool>(evtInfo->auxdata<char>(std::string(m_trigpass_prefix+trigger2.Data())));
// cout <<"bool2:"<<bool2<< endl;
// auto bool3 = static_cast<bool>(evtInfo->auxdata<char>(std::string(m_trigpass_prefix+trigger3.Data())));
// cout <<"bool3:"<<bool3<< endl;
// auto bool4 = static_cast<bool>(evtInfo->auxdata<char>(std::string(m_trigpass_prefix+trigger4.Data())));
// cout <<"bool4:"<<bool4<< endl;
// auto bool5 = static_cast<bool>(evtInfo->auxdata<char>(std::string(m_trigpass_prefix+trigger5.Data())));
// cout <<"bool5:"<<bool5<< endl;
// auto bool6 = static_cast<bool>(evtInfo->auxdata<char>(std::string(m_trigpass_prefix+trigger6.Data())));
// cout <<"bool6:"<<bool6<< endl;
// auto bool7 = static_cast<bool>(evtInfo->auxdata<char>(std::string(m_trigpass_prefix+trigger7.Data())));
// cout <<"bool7:"<<bool7<< endl;
// auto bool8 = static_cast<bool>(evtInfo->auxdata<char>(std::string(m_trigpass_prefix+trigger8.Data())));
// cout <<"bool8:"<<bool8<< endl;
  return static_cast<bool>(evtInfo->auxdata<char>(std::string(m_trigpass_prefix+trigger.Data())));
}

//______________________________________________________________________________________________
bool HWWTrigBase::isPassedAnySingleEl(const xAOD::EventInfo* evtInfo, const HWWTrigConfig* trigConf) const {
  const bool isMC = evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION);
  bool passed = false;
  DEBUGclass("Inside isPassedAnySingleElTrigger");
  for(const auto& trig: (isMC ? trigConf->elecTrigsMC : trigConf->elecTrigsData)){
    DEBUGclass(TString::Format("Inside isPassedAnySingleElTrigger :: checking trigger %s", trig.Data()).Data());
    passed |= isPassedTrigger(evtInfo,trig);
  }
  DEBUGclass(TString::Format("Inside isPassedAnySingleElTrigger :: returning %d", passed).Data());
  return passed;
}

//______________________________________________________________________________________________
bool HWWTrigBase::isPassedAnySingleEl(const xAOD::EventInfo* evtInfo) const {
  const HWWTrigConfig* trigConf = getTrigConfig(evtInfo);
  if (!trigConf) {
    // there seem to be events in MC with RandomRunNr = 0. Coming from mu not represented and thus having weight=0? Previous implementation must then have said false.
    if (evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) {
      if (evtInfo->auxdata<unsigned int>("RandomRunNumber") == 0) {
        // std::cout << "WARNING in HWWTrigBase :: RandomRunNumber == 0, interpreting as trigger miss." << std::endl;
        return false;
      }
    }
    throw std::runtime_error("In HWWTrigBase::isPassedAnySingleEl :: invalid HWWTrigConfig pointer! Are you sure you passed the TrigConfig objects to your observable? Also check with what run numbers they are configured.");
  }
  return isPassedAnySingleEl(evtInfo, trigConf);
}

//______________________________________________________________________________________________
bool HWWTrigBase::isPassedAnySingleMu(const xAOD::EventInfo* evtInfo, const HWWTrigConfig* trigConf) const {
	const bool isMC = evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION);
	bool passed = false;
  DEBUGclass("Inside isPassedAnySingleMuTrigger");
  for(const auto& trig: (isMC ? trigConf->muonTrigsMC : trigConf->muonTrigsData)){
    DEBUGclass(TString::Format("Inside isPassedAnySingleMuTrigger :: checking trigger %s", trig.Data()).Data());
    passed |= isPassedTrigger(evtInfo,trig);
  }
  DEBUGclass(TString::Format("Inside isPassedAnySingleMuTrigger :: returning %d", passed).Data());
  return passed;
}

//______________________________________________________________________________________________
bool HWWTrigBase::isPassedAnySingleMu(const xAOD::EventInfo* evtInfo) const {
  const HWWTrigConfig* trigConf = getTrigConfig(evtInfo);
  if (!trigConf) {
    // there seem to be events in MC with RandomRunNr = 0. Coming from mu not represented and thus having weight=0? Previous implementation must then have said false.
    if (evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) {
      if (evtInfo->auxdata<unsigned int>("RandomRunNumber") == 0) {
        // std::cout << "WARNING in HWWTrigBase :: RandomRunNumber == 0, interpreting as trigger miss." << std::endl;
        return false;
      }
    }
    throw std::runtime_error("In HWWTrigBase::isPassedAnySingleEl :: invalid HWWTrigConfig pointer! Are you sure you passed the TrigConfig objects to your observable? Also check with what run numbers they are configured.");
  }
  return isPassedAnySingleMu(evtInfo, trigConf);
}

//______________________________________________________________________________________________
bool HWWTrigBase::isPassedAnyDilep(const xAOD::EventInfo* evtInfo, const HWWTrigConfig* trigConf) const {
	const bool isMC = evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION);
	bool passed = false;
  for(const auto& trig: (isMC ? trigConf->dilepTrigsMC : trigConf->dilepTrigsData)){
    passed |= isPassedTrigger(evtInfo,trig);
  }
  return passed;
}

//______________________________________________________________________________________________
bool HWWTrigBase::isPassedAnyDilep(const xAOD::EventInfo* evtInfo) const {
  const HWWTrigConfig* trigConf = getTrigConfig(evtInfo);
  if (!trigConf) {
    // there seem to be events in MC with RandomRunNr = 0. Coming from mu not represented and thus having weight=0? Previous implementation must then have said false.
    if (evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) {
      if (evtInfo->auxdata<unsigned int>("RandomRunNumber") == 0) {
        //std::cout << "WARNING in HWWTrigBase :: RandomRunNumber == 0, interpreting as trigger miss." << std::endl;
        return false;
      }
    }
    throw std::runtime_error("In HWWTrigBase::isPassedAnyDilep :: invalid HWWTrigConfig pointer! Are you sure you passed the TrigConfig objects to your observable? Also check with what run numbers they are configured.");
  }
  if (trigConf->useDilepTrigs) return isPassedAnyDilep(evtInfo, trigConf);
  DEBUGclass("You flagged not to use dilep triggers. Returning false.");
  return false;
}
//______________________________________________________________________________________________
bool HWWTrigBase::isPassedAnyDimu(const xAOD::EventInfo* evtInfo, const HWWTrigConfig* trigConf) const {
	const bool isMC = evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION);
	bool passed = false;
  DEBUGclass("Inside isPassedAnyDimuTrigger");
  for(const auto& trig: (isMC ? trigConf->dimuTrigsMC : trigConf->dimuTrigsData)){
    DEBUGclass(TString::Format("Inside isPassedAnyDimuTrigger :: checking trigger %s", trig.Data()).Data());
    passed |= isPassedTrigger(evtInfo,trig);
  }
  DEBUGclass(TString::Format("Inside isPassedAnyDimuTrigger :: returning %d", passed).Data());
  return passed;
}

//______________________________________________________________________________________________
bool HWWTrigBase::isPassedAny(const xAOD::EventInfo* evtInfo, const HWWTrigConfig* trigConfig) const {
  return (isPassedAnySingleEl(evtInfo, trigConfig) || isPassedAnySingleMu(evtInfo, trigConfig) || isPassedAnyDilep(evtInfo, trigConfig) || isPassedAnyDimu(evtInfo, trigConfig));
}

//______________________________________________________________________________________________
bool HWWTrigBase::isPassedAnySingleLep(const xAOD::EventInfo* evtInfo, const HWWTrigConfig* trigConfig) const {
  return (isPassedAnySingleEl(evtInfo, trigConfig) || isPassedAnySingleMu(evtInfo, trigConfig));
}

//______________________________________________________________________________________________
bool HWWTrigBase::isPassedAny(const xAOD::EventInfo* evtInfo) const {
  const HWWTrigConfig* trigConf = getTrigConfig(evtInfo);
  if (!trigConf) {
    if (evtInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) {
      if (evtInfo->auxdata<unsigned int>("RandomRunNumber") == 0) {
        // there seem to be events in MC with RandomRunNr = 0. Coming from mu not represented and thus having weight=0? Previous implementation must then have said false.
        return false;
      }
    }
    throw std::runtime_error("In HWWTrigBase::isPassedAnyDilep :: invalid HWWTrigConfig pointer! Are you sure you passed the TrigConfig objects to your observable? Also check with what run numbers they are configured.");
  }
  if (trigConf->useDilepTrigs) {
    DEBUGclass("Inside HWWTrigBase :: you are using dilepton triggers");
    return isPassedAny(evtInfo, trigConf);
  }
  return isPassedAny(evtInfo, trigConf);
}
