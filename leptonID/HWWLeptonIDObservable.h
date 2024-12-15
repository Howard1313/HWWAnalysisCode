//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __HWWLEPTONIDOBSERVABLE__
#define __HWWLEPTONIDOBSERVABLE__
#include "CAFxAODUtils/TQEventObservable.h"
#include "HWWAnalysisCode/HWWLeptonIDHelper.h"
#include "xAODParticleEvent/CompositeParticleContainer.h"

// which lepton to check and what to check for
enum HWWLepIDModeOfRunning {
  LeadLepID,
  SubleadLepID,
  ThirdLepID,
  FourthLepID,
  OtherLepID,
  LeadLepAntiID,
  SubleadLepAntiID,
  ThirdLepAntiID,
  FourthLepAntiID,
  OtherLepAntiID,
  lvqqSubleadLepID,
  lvqqThirdLepID,
  Muon1ID,
  Muon2ID,
  Muon3ID,
  Ele1ID,
  Ele2ID,
  Lep1ID,
  Lep2ID,
};

// type of analysis being performed
enum HWWAnalysisType {
  OneLep,
  TwoLep,
  WH,
  ZH
};

class HWWLeptonIDObservable : public TQEventObservable {

private:

  // LeptonIDHelper for anti-id and id selections

  // LeptonIDHelper for anti-id and id selections
  const HWW::HWWLeptonIDHelper* fLeptonIDHelper = nullptr;

  /** mode of running, which lepton to check on **/
  HWWLepIDModeOfRunning fHWWLepIDModeOfRunning;

  HWWAnalysisType fHWWAnalysisType;

  const unsigned int fIndexLeadLep;
  const unsigned int fIndexSubleadLep;
  const unsigned int fIndexThirdLep;
  const unsigned int fIndexFourthLep;
  const unsigned int fIndexOtherLep;

protected:
  // put here data members you wish to retrieve
  // be careful to declare them as follows:
  // mutable ClassName const * varname = 0
  // the "mutable" keyword ensures that this member can be changed also by const functions
  // the "const" keyword ensures that const containers can be retrieved
  // for example, use
  mutable xAOD::CompositeParticleContainer const * mCand = 0;




public:
  virtual double getValue() const override;
  virtual bool initializeSelf() override;
  TString mCandName = "";
  // getClone override (so we don't have to rely on root streamer)
  TQObservable* getClone() const override;

public:
  // default constructor
  HWWLeptonIDObservable();
  // copy constructor
  HWWLeptonIDObservable(const HWWLeptonIDObservable& obs);
  // nominal constructor
  HWWLeptonIDObservable(const TString& name, const HWW::HWWLeptonIDHelper* lepIDHelper, const int mode_of_running, const int analysis_type,
                          const unsigned int indexLeadLep = 0, const unsigned int indexSubleadLep = 1,
                           const unsigned int indexThirdLep = 2, const unsigned int indexFourthLep = 3, const unsigned int indexOtherLep = 0);
  virtual ~HWWLeptonIDObservable();
  ClassDefOverride(HWWLeptonIDObservable, 1);

private:
  static bool cmp_pt_IParticle (const xAOD::IParticle* a,const xAOD::IParticle* b);
  static bool cmp_pt_Muon (const xAOD::Muon* a,const xAOD::Muon* b);
  static bool cmp_pt_Electron (const xAOD::Electron* a,const xAOD::Electron* b);
};
#endif