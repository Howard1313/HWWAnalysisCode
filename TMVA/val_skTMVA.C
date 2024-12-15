# Author: Yuriy Ilchenko (ilchenko@physics.utexas.edu)
# Compare two ROC curves from scikit-learn and from TMVA (using skTMVA converter)

import os
import sys

if os.environ['TERM'] == 'xterm':
    os.environ['TERM'] = 'vt100'
# Now it's OK to import readline :)
# Import ROOT libraries

import ROOT
import array
import pandas as pd

from sklearn import tree
import _pickle as cPickle

import numpy as np

cut_mode=0
mode=0
channel=["1u1e","2u0e","1u1ep1em","1u1up1um"]

if cut_mode==0:
    csv_path="/home/student/ML_lvqq/csv_data/csv_data1/"+channel[mode]
    path = "./BDT_trained_Model/"
    
bkg_train = pd.read_csv(csv_path+"/bkg_train_"+channel[mode]+".csv")
bkg_test = pd.read_csv(csv_path+"/bkg_test_"+channel[mode]+".csv")
sig_train = pd.read_csv(csv_path+"/sig_train_"+channel[mode]+".csv")
sig_test = pd.read_csv(csv_path+"/sig_test_"+channel[mode]+".csv")


print("{:^8}{:^8}".format(len(bkg_train),len(bkg_test)))
print("{:^8}{:^8}".format(len(sig_train),len(sig_test)))

import csv

with open('feature_list.csv', newline='') as f:
    reader = csv.reader(f)
    feature_list = list(reader)

print(feature_list)
feature=feature_list[mode]

total_bkg = pd.concat([bkg_train, bkg_test], ignore_index=True)
total_sig = pd.concat([sig_train, sig_test], ignore_index=True)

#n_test=min(len(total_bkg),len(total_sig))
n_test=100

X_total_bkg=total_bkg[feature][0:n_test]
X_total_sig=total_sig[feature][0:n_test]
Y_total_bkg=total_bkg["target"][0:n_test]
Y_total_sig=total_sig["target"][0:n_test]


# X_train=(X_train-X_train.mean(axis=0))/X_train.std(axis=0)
# X_test=(X_test-X_test.mean(axis=0))/X_test.std(axis=0)

X_total_bkg=X_total_bkg.values
X_total_sig=X_total_sig.values
Y_total_bkg=Y_total_bkg.values
Y_total_sig=Y_total_sig.values


# sklearn, get BDT from pickle file
GBDT_skTMVA = open('/home/student/koza4ok/trained_model_pkl/GBDT_skTMVA.pkl', 'rb') 
GBDT = cPickle.load(GBDT_skTMVA)

Ada_skTMVA = open('/home/student/koza4ok/trained_model_pkl/Ada_skTMVA.pkl', 'rb') 
Ada = cPickle.load(Ada_skTMVA)

# create TMVA reader
reader = ROOT.TMVA.Reader()

var_list=[]
for i in range(len(feature)):
	var_list.append(array.array('f',[0.]))

reader = ROOT.TMVA.Reader()
for i in range(len(feature)):
	print(feature[i])
	reader.AddVariable(feature[i], var_list[i])

# TMVA, get BDT from the xml file
reader.BookMVA("GBDT", '/home/student/koza4ok/trained_model_xml/GBDT_skTMVA.weights.xml')
reader.BookMVA("Ada", '/home/student/koza4ok/trained_model_xml/Ada_skTMVA.weights.xml')

# # evaluate sig y predict
sk_y_predicted_GBDT_sig=[]
tmva_y_predicted_GBDT_sig=[]
sk_y_predicted_Ada_sig=[]
tmva_y_predicted_Ada_sig=[]
for i in range(len(X_total_sig)):
    for j in range(len(feature)):
        var_list[j][0]=X_total_sig[i][j]
    score_GBDT_sig = GBDT.decision_function([X_total_sig[i]]).item(0)
    score_Ada_sig = Ada.decision_function([X_total_sig[i]]).item(0)
    GBDTOutput_sig = reader.EvaluateMVA("GBDT")
    AdaOutput_sig = reader.EvaluateMVA("Ada")

    sk_y_predicted_GBDT_sig.append(score_GBDT_sig)
    sk_y_predicted_Ada_sig.append(score_Ada_sig)
    tmva_y_predicted_GBDT_sig.append(GBDTOutput_sig)
    tmva_y_predicted_Ada_sig.append(AdaOutput_sig)

sk_y_predicted_GBDT_sig = np.array(sk_y_predicted_GBDT_sig)
tmva_y_predicted_GBDT_sig = np.array(tmva_y_predicted_GBDT_sig)
sk_y_predicted_Ada_sig = np.array(sk_y_predicted_Ada_sig)
tmva_y_predicted_Ada_sig = np.array(tmva_y_predicted_Ada_sig)

# evaluate bkg y predict
sk_y_predicted_GBDT_bkg=[]
tmva_y_predicted_GBDT_bkg=[]
sk_y_predicted_Ada_bkg=[]
tmva_y_predicted_Ada_bkg=[]
for i in range(len(X_total_bkg)):
    for j in range(len(feature)):
        var_list[j][0]=X_total_bkg[i][j]
    score_GBDT_bkg = GBDT.decision_function([X_total_bkg[i]]).item(0)
    score_Ada_bkg = Ada.decision_function([X_total_bkg[i]]).item(0)
    GBDTOutput_bkg = reader.EvaluateMVA("GBDT")
    AdaOutput_bkg = reader.EvaluateMVA("Ada")

    sk_y_predicted_GBDT_bkg.append(score_GBDT_bkg)
    sk_y_predicted_Ada_bkg.append(score_Ada_bkg)
    tmva_y_predicted_GBDT_bkg.append(GBDTOutput_bkg)
    tmva_y_predicted_Ada_bkg.append(AdaOutput_bkg)

sk_y_predicted_GBDT_bkg = np.array(sk_y_predicted_GBDT_bkg)
tmva_y_predicted_GBDT_bkg = np.array(tmva_y_predicted_GBDT_bkg)
sk_y_predicted_Ada_bkg = np.array(sk_y_predicted_Ada_bkg)
tmva_y_predicted_Ada_bkg = np.array(tmva_y_predicted_Ada_bkg)

# Draw hist
plt.figure(figsize=(10,8))
pridict_model="GBDT_sk"

bkg_hist, bkg_bins = np.histogram(sk_y_predicted_GBDT_bkg, bins=xbin)
plt.step(bkg_bins[:-1], bkg_hist.astype(np.float32)/sum(bkg_hist)/0.02 ,"-",color = "green", where='mid',linewidth=5, alpha=0.7,label="bkg") 
sig_hist, sig_bins = np.histogram(sk_y_predicted_GBDT_sig, bins=xbin)
plt.step(sig_bins[:-1], sig_hist.astype(np.float32)/sum(sig_hist)/0.02 ,"-.",color = "red", where='mid',linewidth=5, alpha=0.7,label="sig") 

plt.title("{a}".format(a=pridict_model),fontsize=30,pad=-350)

plt.xlim(-1,1)
plt.tick_params(axis='x', labelsize=25)
plt.tick_params(axis='y', labelsize=25)
plt.xlabel("score({0})".format("sig"), fontsize=30,horizontalalignment='right',x=1)
plt.ylabel("$1/N\,\,dN/d (score({0}))$".format("sig"),fontsize=30,horizontalalignment='right',y=1)
plt.legend(bbox_to_anchor=(1, 1),ncol=2,fontsize=25)
plt.tight_layout()
plt.savefig(pridict_model+"_hist")

# Draw hist
plt.figure(figsize=(10,8))
pridict_model="GBDT_tmva"

bkg_hist, bkg_bins = np.histogram(tmva_y_predicted_GBDT_bkg, bins=xbin)
plt.step(bkg_bins[:-1], bkg_hist.astype(np.float32)/sum(bkg_hist)/0.02 ,"-",color = "green", where='mid',linewidth=5, alpha=0.7,label="bkg") 
sig_hist, sig_bins = np.histogram(tmva_y_predicted_GBDT_sig, bins=xbin)
plt.step(sig_bins[:-1], sig_hist.astype(np.float32)/sum(sig_hist)/0.02 ,"-.",color = "red", where='mid',linewidth=5, alpha=0.7,label="sig") 

plt.title("{a}".format(a=pridict_model),fontsize=30,pad=-350)

plt.xlim(-1,1)
plt.tick_params(axis='x', labelsize=25)
plt.tick_params(axis='y', labelsize=25)
plt.xlabel("score({0})".format("sig"), fontsize=30,horizontalalignment='right',x=1)
plt.ylabel("$1/N\,\,dN/d (score({0}))$".format("sig"),fontsize=30,horizontalalignment='right',y=1)
plt.legend(bbox_to_anchor=(1, 1),ncol=2,fontsize=25)
plt.tight_layout()
plt.savefig(pridict_model+"_hist")

# Draw hist
plt.figure(figsize=(10,8))
pridict_model="Ada_sk"

bkg_hist, bkg_bins = np.histogram(sk_y_predicted_Ada_bkg, bins=xbin)
plt.step(bkg_bins[:-1], bkg_hist.astype(np.float32)/sum(bkg_hist)/0.02 ,"-",color = "green", where='mid',linewidth=5, alpha=0.7,label="bkg") 
sig_hist, sig_bins = np.histogram(sk_y_predicted_Ada_sig, bins=xbin)
plt.step(sig_bins[:-1], sig_hist.astype(np.float32)/sum(sig_hist)/0.02 ,"-.",color = "red", where='mid',linewidth=5, alpha=0.7,label="sig") 

plt.title("{a}".format(a=pridict_model),fontsize=30,pad=-350)

plt.xlim(-1,1)
plt.tick_params(axis='x', labelsize=25)
plt.tick_params(axis='y', labelsize=25)
plt.xlabel("score({0})".format("sig"), fontsize=30,horizontalalignment='right',x=1)
plt.ylabel("$1/N\,\,dN/d (score({0}))$".format("sig"),fontsize=30,horizontalalignment='right',y=1)
plt.legend(bbox_to_anchor=(1, 1),ncol=2,fontsize=25)
plt.tight_layout()
plt.savefig(pridict_model+"_hist")

# Draw hist
plt.figure(figsize=(10,8))
pridict_model="Ada_tmva"

bkg_hist, bkg_bins = np.histogram(tmva_y_predicted_Ada_bkg, bins=xbin)
plt.step(bkg_bins[:-1], bkg_hist.astype(np.float32)/sum(bkg_hist)/0.02 ,"-",color = "green", where='mid',linewidth=5, alpha=0.7,label="bkg") 
sig_hist, sig_bins = np.histogram(tmva_y_predicted_Ada_sig, bins=xbin)
plt.step(sig_bins[:-1], sig_hist.astype(np.float32)/sum(sig_hist)/0.02 ,"-.",color = "red", where='mid',linewidth=5, alpha=0.7,label="sig") 

plt.title("{a}".format(a=pridict_model),fontsize=30,pad=-350)

plt.xlim(-1,1)
plt.tick_params(axis='x', labelsize=25)
plt.tick_params(axis='y', labelsize=25)
plt.xlabel("score({0})".format("sig"), fontsize=30,horizontalalignment='right',x=1)
plt.ylabel("$1/N\,\,dN/d (score({0}))$".format("sig"),fontsize=30,horizontalalignment='right',y=1)
plt.legend(bbox_to_anchor=(1, 1),ncol=2,fontsize=25)
plt.tight_layout()
plt.savefig(pridict_model+"_hist")










