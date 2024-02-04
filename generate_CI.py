
"""
from scipy.stats import qmc

sampler = qmc.LatinHypercube(d=12)

sample = sampler.random(n=1000)

u_bounds = [1,1,1,1,5000/17282163.0,1,1,1,1,1,1,1]

l_bounds = [0.000000000000001,0.000000000000001,0.000000000000001,0.000000000000001,0.000000000000001,0.000000000000001,0.000000000000001,0.000000000000001,0.000000000000001,0.000000000000001,0.000000000000001,0.000000000000001]

sample_scaled = qmc.scale(sample, l_bounds, u_bounds)

#print(qmc.discrepancy(sample_scaled))


print(len(sample_scaled))

mask = (sample_scaled[:, 0] + sample_scaled[:, 1] < 1) 
filtered_samples = sample_scaled[mask]
mask = (filtered_samples[:, 2] + filtered_samples[:, 3] < 1) 
filtered_samples = filtered_samples[mask]

print(len(filtered_samples))

"""

import numpy as np
import pandas as pd

# Vos limites supérieures et inférieures
u_bounds = [1,1,1,1,5000/17282163.0,1,1,1,1,1,1,1]
l_bounds = [0.000000000000001]*12

# Noms de base pour les colonnes
base_names = ["delta","gamma","eps","r","x0_infect","beta0","beta1","beta2","beta3","beta4","beta5","beta6"]

# Nombre de classes
num_classes = 1  # Remplacez par le nombre de classes que vous avez

# Créer un DataFrame vide avec les noms de colonnes appropriés
column_names = [f"{name}_{i}" for i in range(num_classes) for name in base_names]
df = pd.DataFrame(columns=column_names)

while len(df) < 100:  # Remplacez 10 par le nombre d'échantillons que vous voulez
    # Générer un échantillon aléatoire uniforme de dimension 12 * num_classes
    sample = [np.random.uniform(low, high) for _ in range(num_classes) for low, high in zip(l_bounds, u_bounds)]
    
    # Vérifier les conditions
    if all(sample[i*12 + 0] + sample[i*12 + 1] < 1 for i in range(0, num_classes)):
        if all(sample[i*12 + 2] + sample[i*12 + 3] < 1 for i in range(0, num_classes)):
        # Ajouter l'échantillon au DataFrame
            df = df._append(pd.Series(sample, index=df.columns), ignore_index=True)

# Afficher le DataFrame
print(df)

df.to_csv("./data/Conditions_initiales/1_classe_CI.csv",index = False)


num_classes = 2  # Remplacez par le nombre de classes que vous avez

# Créer un DataFrame vide avec les noms de colonnes appropriés
column_names = [f"{name}_{i}" for i in range(num_classes) for name in base_names]
df = pd.DataFrame(columns=column_names)

while len(df) < 100:  # Remplacez 10 par le nombre d'échantillons que vous voulez
    # Générer un échantillon aléatoire uniforme de dimension 12 * num_classes
    sample = [np.random.uniform(low, high) for _ in range(num_classes) for low, high in zip(l_bounds, u_bounds)]
    
    # Vérifier les conditions
    if all(sample[i*12 + 0] + sample[i*12 + 1] < 1 for i in range(0, num_classes)):
        if all(sample[i*12 + 2] + sample[i*12 + 3] < 1 for i in range(0, num_classes)):
        # Ajouter l'échantillon au DataFrame
            df = df._append(pd.Series(sample, index=df.columns), ignore_index=True)

# Afficher le DataFrame
print(df)

df.to_csv("./data/Conditions_initiales/2_classe_CI.csv",index = False)





num_classes = 4  # Remplacez par le nombre de classes que vous avez

# Créer un DataFrame vide avec les noms de colonnes appropriés
column_names = [f"{name}_{i}" for i in range(num_classes) for name in base_names]
df = pd.DataFrame(columns=column_names)

while len(df) < 100:  # Remplacez 10 par le nombre d'échantillons que vous voulez
    # Générer un échantillon aléatoire uniforme de dimension 12 * num_classes
    sample = [np.random.uniform(low, high) for _ in range(num_classes) for low, high in zip(l_bounds, u_bounds)]
    
    # Vérifier les conditions
    if all(sample[i*12 + 0] + sample[i*12 + 1] < 1 for i in range(0, num_classes)):
        if all(sample[i*12 + 2] + sample[i*12 + 3] < 1 for i in range(0, num_classes)):
        # Ajouter l'échantillon au DataFrame
            df = df._append(pd.Series(sample, index=df.columns), ignore_index=True)

# Afficher le DataFrame
print(df)

df.to_csv("./data/Conditions_initiales/4_classe_CI.csv",index = False)





num_classes = 8  # Remplacez par le nombre de classes que vous avez

# Créer un DataFrame vide avec les noms de colonnes appropriés
column_names = [f"{name}_{i}" for i in range(num_classes) for name in base_names]
df = pd.DataFrame(columns=column_names)
ite=0
while len(df) < 100:  # Remplacez 10 par le nombre d'échantillons que vous voulez
    # Générer un échantillon aléatoire uniforme de dimension 12 * num_classes
    sample = [np.random.uniform(low, high) for _ in range(num_classes) for low, high in zip(l_bounds, u_bounds)]
    
    # Vérifier les conditions
    if all(sample[i*12 + 0] + sample[i*12 + 1] < 1 for i in range(0, num_classes)):
        if all(sample[i*12 + 2] + sample[i*12 + 3] < 1 for i in range(0, num_classes)):
        # Ajouter l'échantillon au DataFrame
            df = df._append(pd.Series(sample, index=df.columns), ignore_index=True)
            ite = ite +1
            print(ite)


# Afficher le DataFrame
print(df)

df.to_csv("./data/Conditions_initiales/8_classe_CI.csv",index = False)

    




#sampler = qmc.LatinHypercube(d=12, optimization="random-cd")

#sample = sampler.random(n=100)
#sample_scaled = qmc.scale(sample, l_bounds, u_bounds)

#print(qmc.discrepancy(sample_scaled))


