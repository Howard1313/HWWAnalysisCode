//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __ZHCAND__
#define __ZHCAND__
#include "CAFxAODUtils/TQEventObservable.h"

#include "xAODParticleEvent/CompositeParticleContainer.h"
class ZHCand : public TQEventObservable {
protected:
  // Put here data members you wish to use.
  // If you would like to create a vector observable
  // you should define the vectors here.
  // The "mutable" keyword ensures that this member
  // can be changed also by const functions.
  // You also might want to add a variable
  // for the name of the xAOD container to be retrieved that
  // will be initialized in the initialize function.
  /* example block
     mutable std::vector<double> myvector = std::vector<double>();
     TString mContName = "";
  */
     mutable std::vector<double> myvector = std::vector<double>();
     TString mContName = "";

  mutable Long64_t fCachedEntry;

  bool makeCache() const;

public:

  const std::vector<double>* getVector() const;
  virtual double getValue() const override;
  virtual double getValueAt(int index) const override;
  virtual int getNevaluations() const override;
  TQObservable::ObservableType fType = TQObservable::ObservableType::vector;
  inline virtual TQObservable::ObservableType getObservableType() const override {
    return fType;
  }
protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
public:
  ZHCand();
  ZHCand(const TString& name);
  virtual ~ZHCand();
  ClassDefOverride(ZHCand, 1);
private:
  class Cmp_pt {
    public:
      bool operator() (const xAOD::IParticle* a,const xAOD::IParticle* b) { // something 
          return a->pt() > b->pt();
      }
      bool operator() (const xAOD::Muon* a,const xAOD::Muon* b) { // something 
          return a->pt() > b->pt();
      }
      bool operator() (const xAOD::Electron* a,const xAOD::Electron* b) { // something 
          return a->pt() > b->pt();
      }
      bool operator() (TLorentzVector a,TLorentzVector b) { // something 
          return a.Pt() > b.Pt();
      }
      bool operator() (const xAOD::Jet* a,const xAOD::Jet* b) { // something 
          return a->pt() > b->pt();
      }
    } cmp_pt;
  float get_mT (TLorentzVector vis, TLorentzVector neutrino) const {
    auto ET=sqrt(vis.M()* vis.M()+ vis.Pt()* vis.Pt());
    return sqrt(2*ET*neutrino.E()*(1-cos(vis.DeltaPhi(neutrino))));
  }
};
#endif