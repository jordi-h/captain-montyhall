/**
 * \file outils.h
 * \brief Gestion des boutons et des labels.
 * \author Hoorelbeke Jordi -- s175615
 * \version 1.0
 * \date 14/04/2019
 */

#ifndef __OUTILS__
#define __OUTILS__

#include <gtk/gtk.h>

/**
 * \enum EtatCoffre
 * \brief Enumération fournissant l'état d'un coffre.
 */
typedef enum {
	ferme = 1,
	vide = 2,
	plein = 3
}EtatCoffre;

/**
 * \struct bouton_t Bouton
 * \brief Structure représentant un bouton.
 */
typedef struct bouton_t{
	EtatCoffre etat;
	char *image;
	GtkWidget *pBouton;
}Bouton;


/**
 * \fn Bouton *creer_bouton(void)
 * \brief Crée une structure de type Bouton.
 *
 * \return bt une variable de type Bouton.
 */
Bouton *creer_bouton(void);

/**
 * \fn void scores_mise_a_jour(GtkWidget *pScore, unsigned int nb_vict, unsigned int nb_def)
 * \brief Mise-à-jour du score.
 *
 * \param pScore le Widget en cause.
 * \param nb_vict le nombre de victoires totale.
 * \param nb_def le nombre de défaites totale.
 */
void scores_mise_a_jour(GtkWidget *pScore, unsigned int nb_vict, unsigned int nb_def);

/**
 * \fn void aleatoire(Bouton *bt1, Bouton *bt2, Bouton *bt3)
 * \brief Affectation aléatoire de l'état et de l'images des boutons.
 *
 * \param bt1 une structure de type Bouton.
 * \param bt2 une structure de type Bouton.
 * \param bt3 une structure de type Bouton.
 */
void aleatoire(Bouton *bt1, Bouton *bt2, Bouton *bt3);

/**
 * \fn void click_recommencer(GtkWidget *pF, gpointer data)
 * \brief reinitialise la partie sans toucher au nombre de victoire/défaites.
 *
 * \param pF le widget en cause. 
 * \param data pointeur vers l'interface.
 */
void click_recommencer(GtkWidget *pF, gpointer data);

/**
 * \fn void click_bouton1(GtkWidget *pF, gpointer data)
 * \brief Signal pour le click du bouton 1.
 *
 * \param pF le widget en cause. 
 * \param data pointeur vers l'interface.
 */
void click_bouton1(GtkWidget *pF, gpointer data);

/**
 * \fn void click_bouton2(GtkWidget *pF, gpointer data)
 * \brief Signal pour le click du bouton 2.
 *
 * \param pF le widget en cause. 
 * \param data pointeur vers l'interface.
 */
void click_bouton2(GtkWidget *pF, gpointer data);

/**
 * \fn void click_bouton3(GtkWidget *pF, gpointer data)
 * \brief Signal pour le click du bouton 3.
 *
 * \param pF le widget en cause.
 * \param data pointeur vers l'interface.
 */
void click_bouton3(GtkWidget *pF, gpointer data);


#endif //__OUTILS__
