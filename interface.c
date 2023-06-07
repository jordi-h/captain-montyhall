/*
 * interface.c
 *
 * Ce fichier contient les fonctions pour la création
 * de la fenêtre et de son interface.
 *
 * @author: Hoorelbeke Jordi -- s175615
 * @date: 14/04/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <gtk/gtk.h>

#include "outils.h"
#include "interface.h"


GtkWidget *creer_fenetre(){
	//création fenêtre
	GtkWidget *pF = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(pF), "Le jeu du trésor");
	gtk_window_set_default_size(GTK_WINDOW(pF), 800, 400);
	gtk_window_set_position(GTK_WINDOW(pF), GTK_WIN_POS_CENTER);

	//Mouchard pour destruction_fenêtre
	g_signal_connect(G_OBJECT(pF), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	return pF;
}

Interface *creer_interface(Bouton *bt1, Bouton *bt2, Bouton *bt3){
	Interface *interface = malloc(sizeof(Interface));
	if(interface==NULL)
		return NULL;

	interface->manche = 1;

	interface->nb_vict = 0;
	interface->nb_def = 0;

	interface->pScore = gtk_label_new("tmp");
	scores_mise_a_jour(interface->pScore, interface->nb_vict, interface->nb_def);
	interface->pLabel = gtk_label_new("Choisissez un coffre!");

	interface->pRecommencer = gtk_button_new_with_mnemonic("_Recommencer");;

	interface->bt1 = bt1;
	interface->bt2 = bt2;
	interface->bt3 = bt3;

	return interface;
}
