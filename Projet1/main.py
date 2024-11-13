import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

def plot_lcs_complexity(filename):
    try:
        df = pd.read_csv(filename)
        
        df_filtered = df[df['taille1'].notnull() & df['taille2'].notnull()]
        
        
        df_filtered['taille_combinee'] = df_filtered['taille1'] + df_filtered['taille2']
        
        
        df_filtered = df_filtered.sort_values('tempsMoyen')
        
        plt.figure(figsize=(10, 6))
        plt.plot(df_filtered['taille_combinee'], 
                         df_filtered['tempsMoyen'],
                         0,
                         color='skyblue',
                         alpha=0.6)
        plt.xlabel('Taille combinée (taille1 + taille2)')
        plt.ylabel('Temps d\'exécution (tempsMoyen)')
        plt.title('Graphique en aire de la Complexité LCS')
        plt.grid(True, alpha=0.3)

        plt.figure(figsize=(10, 6))
        plt.fill_between(df_filtered['taille_combinee'], 
                         df_filtered['TailleMem'],
                         0,
                         color='skyblue',
                         alpha=0.6)
        plt.xlabel('Taille combinée (taille1 + taille2)')
        plt.ylabel('Taille mémoire (TailleMem)')
        plt.title('Graphique en aire de la Complexité LCS (TailleMémoire)')
        plt.grid(True, alpha=0.3)

        plt.show()

    except FileNotFoundError:
        print(f"Erreur: Le fichier '{filename}' n'a pas été trouvé.")
    except Exception as e:
        print(f"Une erreur s'est produite: {str(e)}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python main.py nom_fichier.csv")
        sys.exit(1)
    
    filename = sys.argv[1]
    plot_lcs_complexity(filename)
