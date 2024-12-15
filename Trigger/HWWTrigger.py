from QFramework import TQObservable, INFO, ERROR, BREAK, WARN
from HWWAnalysisCode import HWWTriggerSelection
from HWWAnalysisCode import HWWTriggerMatchingObs
from HWWAnalysisCode import HWWTriggeringPart

def getTriggerSelectionObs(name, triggerConfigs):
  obs = HWWTriggerSelection(name)
  for t in triggerConfigs:
    obs.addTriggerConfig(t)
  return obs
def getTriggerMatchingObs(name, triggerConfigs):
  obs = HWWTriggerMatchingObs(name)
  for t in triggerConfigs:
    obs.addTriggerConfig(t)
  return obs
def getTriggeringPartObs(name, triggerConfigs, part, lep = HWWTriggeringPart.LepFlavour.ALL, trig = HWWTriggeringPart.TrigType.ANY):
  obs = HWWTriggeringPart(name, part, lep, trig)
  for t in triggerConfigs:
    obs.addTriggerConfig(t)
  return obs

def addObservables(config):
  INFO("adding different trigger observables and trigger matching tools")

  #======================
  #===== import trigger config, needed by trigger observables
  try:
    from HWWAnalysisCode import TrigConfig
  except Exception as error:
    ERROR("Couldn't import TrigConfig module!\n" + "Message from python:\n" + str(error))
    return False

  #======================
  #===== import lepton ID helper snippet, will pass object to observables that need it
  try:
    from HWWAnalysisCode import LeptonIDHelper
  except Exception as error:
    ERROR("Couldn't import LeptonIDHelper module!\n" + "Message from python:\n" + str(error))
    return False
  lepIDSelectionTag = config.getTagStringDefault("lepIDSelectionTag", "VH")
  lepIDHelper = LeptonIDHelper.getLepIDHelper(lepIDSelectionTag)
  INFO("in HWWTrigger: Using lepton ID selection '{}' (see HWWAnalysisCode/python/LeptonIDHelper.py for details)".format(lepIDSelectionTag))

  ### which triggers to use and for what periods are specified in the HWWTrigConfig.py snippet
  ### these objects will be passed to and operated on by the trigger selection/matching observables
  ### initialised below
  # triggers to use: single-lepton + one of the dilepton triggers ("HLT_e17_lhloose.._mu14")
  triggerConfigs = TrigConfig.getTrigConfigsDilep1()
  # only single-lepton triggers
  triggerConfigsSingleLepOnly = TrigConfig.getTrigConfigs()
  # only dilepton triggers (using one dilepton trigger per period)
  triggerConfigsDimu = TrigConfig.getTrigConfigsDimu()
  
  triggerConfigsDilepOnly = TrigConfig.getTrigConfigsDilep1__OnlyDilep()
  # Using both dilepton and single lepton triggers
  triggerConfigsBothDilep = TrigConfig.getTrigConfigsDilep()

  #=================
  #=== trigger selection observables
  #=================
  # trigger decision observables will return true/false for the trigger decision,
  # assuming an OR between the triggers you put in your triggerConfigs objects.
  TriggerSelectionObs = getTriggerSelectionObs("TriggerSelectionObs", triggerConfigs)
  if not TQObservable.addObservable(TriggerSelectionObs):
    ERROR("Failed to register trigger selection observable")
    return False

  #For single-lepton-triggers only
  TriggerSelectionSingleLepOnlyObs = getTriggerSelectionObs("TriggerSelectionSingleLepOnlyObs", triggerConfigsSingleLepOnly)
  if not TQObservable.addObservable(TriggerSelectionSingleLepOnlyObs):
    ERROR("Failed to register trigger selection observable for single-lepton-only triggers")
    return False

  #For dimu-triggers 
  TriggerSelectionDimuObs = getTriggerSelectionObs("TriggerSelectionDimuObs", triggerConfigsDimu)
  if not TQObservable.addObservable(TriggerSelectionDimuObs):
    ERROR("Failed to register trigger selection observable for Dimu triggers")
    return False

  #For dilepton-triggers only
  TriggerSelectionDilepOnlyObs = getTriggerSelectionObs("TriggerSelectionDilepOnlyObs", triggerConfigsDilepOnly)
  if not TQObservable.addObservable(TriggerSelectionDilepOnlyObs):
    ERROR("Failed to register trigger selection observable for dilepton-only triggers")
    return False

  #For using both dilepton triggers with single lepton triggers
  TriggerSelectionBothDilepObs = getTriggerSelectionObs("TriggerSelectionBothDilepObs", triggerConfigsBothDilep)
  if not TQObservable.addObservable(TriggerSelectionBothDilepObs):
    ERROR("Failed to register trigger selection observable for both dilepton + single lepton triggers")
    return False

  #=================
  #=== trigger matching observables
  #=================
  # trigger matching observables will return true/false if there is a trigger match,
  # assuming an OR between the triggers you put in your triggerConfigs objects.
  TriggerMatchingObs = getTriggerMatchingObs("TriggerMatchingObs", triggerConfigs)
  if not TQObservable.addObservable(TriggerMatchingObs):
    ERROR("Failed to register trigger matching observable")
    return False

  TriggerMatchingSingleLepOnlyObs = getTriggerMatchingObs("TriggerMatchingSingleLepOnlyObs", triggerConfigsSingleLepOnly)
  if not TQObservable.addObservable(TriggerMatchingSingleLepOnlyObs):
    ERROR("Failed to register trigger matching observable")
    return False

  TriggerMatchingDimuObs = getTriggerMatchingObs("TriggerMatchingDimuObs", triggerConfigsDimu)
  if not TQObservable.addObservable(TriggerMatchingDimuObs):
    ERROR("Failed to register trigger matching observable")
    return False

  TriggerMatchingBothDilepObs = getTriggerMatchingObs("TriggerMatchingBothDilepObs", triggerConfigsBothDilep)
  if not TQObservable.addObservable(TriggerMatchingBothDilepObs):
    ERROR("Failed to register trigger matching observable")
    return False

  ##=============================
  #==== Which part of the event fired a trigger?
  #=============================

  lep0FiredSingleLepTrigger = getTriggeringPartObs('lep0FiredSingleLepTrigger', triggerConfigs, 0, HWWTriggeringPart.LepFlavour.ALL,      HWWTriggeringPart.TrigType.SINGLE)
  lep1FiredSingleLepTrigger = getTriggeringPartObs('lep1FiredSingleLepTrigger', triggerConfigs, 1, HWWTriggeringPart.LepFlavour.ALL,      HWWTriggeringPart.TrigType.SINGLE)

  if not TQObservable.addObservable(lep0FiredSingleLepTrigger):
    INFO('Failed to add observable \'lep0FiredSingleLepTrigger\'.')
    return False
  if not TQObservable.addObservable(lep1FiredSingleLepTrigger):
    INFO('Failed to add observable \'lep1FiredSingleLepTrigger\'.')
    return False

  return True

if __name__ == "__main__":
  print("Inside main of HWWTrigger snippet, will now call addObservables")
  from QFramework import TQTaggable
  tags = TQTaggable()
  addObservables(tags)
