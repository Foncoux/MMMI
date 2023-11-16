import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os



# Utilisez la fonction read_csv de pandas pour lire le fichier
import csv

classe = 2
# Spécifiez le chemin du fichier CSV
filename = "./data/MCMC_param/save_MCMC"


import pandas as pd
import glob



# Utilisez la bibliothèque glob pour obtenir la liste des fichiers CSV dans le répertoire
liste_fichiers_csv = glob.glob(filename + '*.csv')

# Initialisez un DataFrame vide
dataframe_global = pd.DataFrame()

# Parcourez chaque fichier CSV et ajoutez ses données au DataFrame global
for fichier_csv in liste_fichiers_csv:
    # Lisez le fichier CSV
    dataframe_temporaire = pd.read_csv(fichier_csv)
    
    # Ajoutez les données au DataFrame global
    dataframe_global = pd.concat([dataframe_global, dataframe_temporaire], ignore_index=True)

# Affichez le DataFrame global
print(dataframe_global)











#N = 21
#x = np.linspace(0, 10, 11)
#y = [3.9, 4.4, 10.8, 10.3, 11.2, 13.1, 14.1,  9.9, 13.9, 15.1, 12.5]

# fit a linear curve and estimate its y-values and their error.
#a, b = np.polyfit(x, y, deg=1)
#y_est = a * x + b
#y_err = x.std() * np.sqrt(1/len(x) +
#                          (x - x.mean())**2 / np.sum((x - x.mean())**2))

#plt.figure(1)

#plt.plot(x, y_est, '-')
#plt.fill_between(x, y_est - y_err, y_est + y_err, alpha=0.2)
#plt.plot(x, y, 'o', color='tab:brown')

#plt.show()
