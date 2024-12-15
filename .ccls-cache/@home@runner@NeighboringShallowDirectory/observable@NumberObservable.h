#include "CAFxAODUtils/TQEventObservable.h"
#include "xAODParticleEvent/CompositeParticleContainer.h"

#ifndef __NumberObservable__
#define __NumberObservable__

enum class Number_Variable {
  njet,
  nSRjet,
  nmuon,
  nmuon_p,
  nmuon_m,
  nele,
  nele_p,
  nele_m,
  nlep,
  sumPt_SRjet,
  Wjj_count
};

// type of analysis being performed


class NumberObservable : public TQEventObservable {

private:

 
  Number_Variable fnumber_variable;

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
  // TQObservable* getClone() const override;

public:
  // default constructor
  NumberObservable();
  // copy constructor
  NumberObservable(const NumberObservable& obs);
  // nominal constructor
  NumberObservable(const TString& name, const int number_variable);
  virtual ~NumberObservable();
  ClassDefOverride(NumberObservable, 1);

private:
static bool cmp_pt_IParticle(std::tuple<const xAOD::IParticle*, int> a,
                             std::tuple<const xAOD::IParticle*, int> b);
static bool cmp_pt_Muon(const xAOD::Muon *a, const xAOD::Muon *b);
static bool cmp_pt_Electron(const xAOD::Electron *a, const xAOD::Electron *b);
static bool cmp_pt_TLorentzVector(TLorentzVector a, TLorentzVector b);
static bool cmp_pt_Jet(const xAOD::Jet *a, const xAOD::Jet *b);
};
#endif