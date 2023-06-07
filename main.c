/*
 * main.c
 * 
 * Ce fichier contient la fonction main() du jeu du trésor.
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


int main(int argc, char **argv){

	//lancement de l'IHM
	GtkWidget *pFenetre;
	GtkWidget *pTable;

	//initialisation de l'environnement GTK
	gtk_init(&argc, &argv);

	//creation de la fenêtre
	pFenetre = creer_fenetre();

	//création des boutons des coffres
	Bouton *bt1 = creer_bouton();
	if(bt1==NULL)
        return EXIT_FAILURE;
	

	Bouton *bt2 = creer_bouton();
	if(bt2==NULL)
        return EXIT_FAILURE;
	
	Bouton *bt3 = creer_bouton();
	if(bt3==NULL)
        return EXIT_FAILURE;
	
	//Remplissage du coffre gagnant
    aleatoire(bt1, bt2, bt3);

	//création de l'inteface
	Interface *interface = creer_interface(bt1, bt2, bt3);
	if(interface==NULL)
        return EXIT_FAILURE;
    
	//Mouchards
	g_signal_connect(G_OBJECT(interface->pRecommencer), "clicked", G_CALLBACK(click_recommencer), interface);
	g_signal_connect(G_OBJECT(bt1->pBouton), "clicked", G_CALLBACK(click_bouton1), interface);
	g_signal_connect(G_OBJECT(bt2->pBouton), "clicked", G_CALLBACK(click_bouton2), interface);
	g_signal_connect(G_OBJECT(bt3->pBouton), "clicked", G_CALLBACK(click_bouton3), interface);

	//création de l'interface (pTable)
	pTable = gtk_table_new(6, 6, FALSE);

	gtk_table_attach(GTK_TABLE(pTable), interface->pScore, 0, 6, 0, 1, GTK_FILL, GTK_FILL, 5, 5);
	gtk_table_attach(GTK_TABLE(pTable), interface->pLabel, 0, 6, 1, 2, GTK_FILL, GTK_FILL, 5, 5);
	gtk_table_attach(GTK_TABLE(pTable), interface->pRecommencer, 0, 6, 2, 3, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(pTable), bt1->pBouton, 0, 2, 3, 6, GTK_EXPAND, GTK_EXPAND, 0, 0);
	gtk_table_attach(GTK_TABLE(pTable), bt2->pBouton, 2, 4, 3, 6, GTK_EXPAND, GTK_EXPAND, 0, 0);
	gtk_table_attach(GTK_TABLE(pTable), bt3->pBouton, 4, 6, 3, 6, GTK_EXPAND, GTK_EXPAND, 0, 0);

	gtk_container_add(GTK_CONTAINER(pFenetre), GTK_WIDGET(pTable));

	//Affichage de la fenêtre et de ses éléments
	gtk_widget_show_all(pFenetre);

	//Boucle des évenements
	gtk_main();

	return EXIT_SUCCESS;
}
