from sklearn.ensemble import GradientBoostingClassifier, AdaBoostClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn import tree
import numpy as np
import tensorflow as tf

from matplotlib import cm
import matplotlib.pyplot as plt
import importlib
import time
from sklearn.datasets import make_hastie_10_2
import pandas as pd
from sklearn.utils import shuffle
from sklearn import metrics
from sklearn import preprocessing
from joblib import dump, load
from sklearn.metrics import confusion_matrix
from tensorflow.keras.utils import to_categorical
import os

from sklearn.model_selection import cross_val_score
from sklearn import svm

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

train_len=min(len(bkg_train),len(sig_train))
test_len=min(len(bkg_test),len(sig_test))
        
X_train_bkg=bkg_train[feature][0:train_len]
X_test_bkg=bkg_test[feature][0:test_len]
X_train_sig=sig_train[feature][0:train_len]
X_test_sig=sig_test[feature][0:test_len]
Y_train_bkg=bkg_train["target"][0:train_len]
Y_test_bkg=bkg_test["target"][0:test_len]
Y_train_sig=sig_train["target"][0:train_len]
Y_test_sig=sig_test["target"][0:test_len]

# X_train_bkg=bkg_train[feature]
# X_test_bkg=bkg_test[feature]
# X_train_sig=sig_train[feature]
# X_test_sig=sig_test[feature]
# Y_train_bkg=bkg_train["target"]
# Y_test_bkg=bkg_test["target"]
# Y_train_sig=sig_train["target"]
# Y_test_sig=sig_test["target"]

total_bkg = pd.concat([bkg_train, bkg_test], ignore_index=True)
total_sig = pd.concat([sig_train, sig_test], ignore_index=True)


X_train=pd.concat([X_train_bkg, X_train_sig], ignore_index=True)
Y_train=pd.concat([Y_train_bkg, Y_train_sig], ignore_index=True)
X_test=pd.concat([X_test_bkg, X_test_sig], ignore_index=True)
Y_test=pd.concat([Y_test_bkg, Y_test_sig], ignore_index=True)
print(len(X_train),len(X_test),len(Y_train),len(Y_test))

var_min=[]
var_max=[]
for i in range(len(feature)):
	var_min.append(min(X_train[feature[i]]))
	var_max.append(max(X_train[feature[i]]))


# X_train=(X_train-X_train.mean(axis=0))/X_train.std(axis=0)
# X_test=(X_test-X_test.mean(axis=0))/X_test.std(axis=0)

X_train=X_train.values
Y_train=Y_train.values
X_test=X_test.values
Y_test=Y_test.values

max_depth=3
max_lerning_rate=0.1
print(time.strftime("%a %b %d %H:%M:%S %Y", time.localtime()))
ticks_1 = time.time()
############################################################################################################################################################

GBDT = 0
for i, filename in enumerate(os.listdir(path)):
    if filename == "clf_GBDT_"+channel[mode]+".h5" :
        GBDT += 1 

if GBDT == 1:
    rand = np.random.randint(1000000)
    # clf_1 = GradientBoostingClassifier(n_estimators=100, learning_rate=0.5, max_depth=1, random_state=0).fit(X,Y)
    clf_GBDT = GradientBoostingClassifier(
                n_estimators=500,
                n_iter_no_change=5,
                validation_fraction=0.2,
                tol=0.001,
                learning_rate=max_lerning_rate,
                max_depth=max_depth, 
                min_samples_split = 0.25,
                min_samples_leaf = 0.05,
    #             min_impurity_split = 0.00001,
    #             validation_fraction = 0.1,
                random_state= rand,  #np.random,
                verbose = 1
                )
    clf_GBDT.fit(X_train,Y_train)
    dump(clf_GBDT, path+"clf_GBDT_"+channel[mode]+".h5")

#     arch = clf_GBDT.to_json()
#     # save the architecture string to a file somehow, the below will work
#     with open(path+"clf_GBDT_arch_"+channel[mode]+".json", 'w') as arch_file:
#         arch_file.write(arch)
#     # now save the weights as an HDF5 file
#     clf_GBDT.save_weights(path+"clf_GBDT_weights_"+channel[mode]+".h5")

ticks_2 = time.time()
    

# if GBDT == 1:
#     clf_GBDT = load(path+"clf_GBDT_"+channel[mode]+".h5")


############################################################################################################################################################
totaltime =  ticks_2 - ticks_1
print("\033[32mTime consumption : {:.4f} min for GBDT\033[0m".format(totaltime/60.))

import _pickle as cPickle
# Save BDT to pickle file
with open('trained_model_pkl/GBDT_skTMVA.pkl', 'wb') as fid:
    cPickle.dump(clf_GBDT, fid)

print(feature)
var_list=[]
for i in range(len(feature)):
    var_list.append((feature[i],"F",var_min[i],var_max[i]))
print(var_list)

from skTMVA import convert_bdt_sklearn_tmva
convert_bdt_sklearn_tmva(clf_GBDT,var_list, 'trained_model_xml/GBDT_skTMVA.xml')