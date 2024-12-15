from QFramework import TQTreeObservable, INFO, ERROR
import ROOT
from HWWAnalysisCode import NumberObservable

class Number_Variable:
  njet        = 0
  nSRjet     = 1
  nmuon       = 2
  nmuon_p      = 3
  nmuon_m       = 4
  nele    = 5
  nele_p = 6
  nele_m   = 7
  nlep    = 8
  sumPt_SRjet  = 9
  Wjj_count  = 10


def addObservables(config):
  from QFramework import TQObservable,INFO,ERROR,BREAK,WARN

  
  # try:
  #   from HWWAnalysisCode import NumberObservable
  # except Exception as error:
  #   ERROR("Couldn't import NumberObservable.h module!\n"+"Message from python:\n"+str(error))
  #   return False


  INFO("adding NumberObservable")
  #=== The integers must match the correct modes inside HWWLeptonIDObservable.cxx
  njet = NumberObservable("njet", Number_Variable.njet)
  if not TQObservable.addObservable(njet): return False
  nSRjet = NumberObservable("nSRjet", Number_Variable.nSRjet)
  if not TQObservable.addObservable(nSRjet): return False
  nmuon = NumberObservable("nmuon", Number_Variable.nmuon)
  if not TQObservable.addObservable(nmuon): return False
  nmuon_p = NumberObservable("nmuon_p", Number_Variable.nmuon_p)
  if not TQObservable.addObservable(nmuon_p): return False
  nmuon_m = NumberObservable("nmuon_m", Number_Variable.nmuon_m)
  if not TQObservable.addObservable(nmuon_m): return False
  nele = NumberObservable("nele", Number_Variable.nele)
  if not TQObservable.addObservable(nele): return False
  nele_p = NumberObservable("nele_p", Number_Variable.nele_p)
  if not TQObservable.addObservable(nele_p): return False
  nele_m = NumberObservable("nele_m", Number_Variable.nele_m)
  if not TQObservable.addObservable(nele_m): return False
  nlep = NumberObservable("nlep", Number_Variable.nlep)
  if not TQObservable.addObservable(nlep): return False
  sumPt_SRjet = NumberObservable("sumPt_SRjet", Number_Variable.sumPt_SRjet)
  if not TQObservable.addObservable(sumPt_SRjet): return False
  Wjj_count = NumberObservable("Wjj_count", Number_Variable.Wjj_count)
  if not TQObservable.addObservable(Wjj_count): return False
    
  return True

if __name__ == "__main__":
  print "Inside main of NumberObservable python snippet"
  if not addObservables():
    print("Couldn't add NumberObservable!")
  else:
    print("Successfully added NumberObservable")


