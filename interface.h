/**
 * \file interface.h
 * \brief Gestion de l'interface.
 * \author Hoorelbeke Jordi -- s175615
 * \version 1.0
 * \date 14/04/2019
 */

#ifndef __INTERFACE__
#define __INTERFACE__

#include <gtk/gtk.h>

/**
 * \struct interface_t Interface
 * \brief Structure représentant l'interface du jeu.
 */
typedef struct interface_t{
	unsigned int manche;
	unsigned int nb_vict;
	unsigned int nb_def;
	GtkWidget *pScore;
	GtkWidget *pLabel;
	GtkWidget *pRecommencer;
	Bouton *bt1;
	Bouton *bt2;
	Bouton *bt3; 
}Interface;


/**
 * \fn GtkWidget *creer_fenetre(void)
 * \brief Crée une fenêtre.
 */
GtkWidget *creer_fenetre(void);

/**
 * \fn Interface *creer_interface(Bouton *bt1, Bouton *bt2, Bouton *bt3)
 * \brief Crée une structure de type Interface.
 *
 * \param bt1 une structure de type Bouton.
 * \param bt2 une structure de type Bouton.
 * \param bt3 une structure de type Bouton.
 */
Interface *creer_interface(Bouton *bt1, Bouton *bt2, Bouton *bt3);


#endif //__INTERFACE__