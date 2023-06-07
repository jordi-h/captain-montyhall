/*
 * outils.c
 *
 * Ce fichier contient les fonctions de manipulation 
 * de boutons et de labels.
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


static GtkWidget *charge_image_bouton(char *nom_image){
	assert(nom_image!=NULL);

	GtkWidget *pBouton;
	GdkPixbuf *pb_temp, *pb;
	GtkWidget *image;

	//1. Charger l'image et la redimensionner (100*100 px)
	pb_temp = gdk_pixbuf_new_from_file(nom_image, NULL);
	if(pb_temp == NULL){
		printf("Erreur de chargement de l'image coffre_ferme.jpg!\n");
		return NULL;
	}
	pb = gdk_pixbuf_scale_simple(pb_temp, 200, 200, GDK_INTERP_NEAREST);

	//2. Créer le bouton
	pBouton = gtk_button_new();

	//3. Placer l'image
	image = gtk_image_new_from_pixbuf(pb);
	gtk_button_set_image(GTK_BUTTON(pBouton), image);

	return pBouton;
}

static GtkWidget *reinitialiser_image(){
	GdkPixbuf *pb_temp, *pb;
	GtkWidget *image;

	pb_temp = gdk_pixbuf_new_from_file("images_coffrets/coffre_ferme.jpg", NULL);
		if(pb_temp == NULL){
			printf("Erreur de chargement de l'image coffre_ferme.jpg!\n");
			return NULL;
		}
	pb = gdk_pixbuf_scale_simple(pb_temp, 200, 200, GDK_INTERP_NEAREST);
	image = gtk_image_new_from_pixbuf(pb);

	return image;
}

Bouton *creer_bouton(){
	Bouton *bt = malloc(sizeof(Bouton));
	if(bt==NULL)
		return NULL;

	bt->etat = ferme;
	bt->image = "images_coffrets/coffre_ferme.jpg";
	bt->pBouton = charge_image_bouton(bt->image);

	return bt;
}

void scores_mise_a_jour(GtkWidget *pScore, unsigned int nb_vict, unsigned int nb_def){
	assert(pScore!=NULL);

	char message[100];
	sprintf(message, "Victoires: %u\tDéfaites: %u", nb_vict, nb_def);
	gtk_label_set_text(GTK_LABEL(pScore), message);
}

void aleatoire(Bouton *bt1, Bouton *bt2, Bouton *bt3){
	assert(bt1!=NULL && bt2!=NULL && bt3!=NULL);

	srand(time(NULL)); //rand dépend du temps pour plus de hasard
	
	//état des coffres en fonction de (rand() % 3 + 1)
	switch(rand() % 3 + 1){
    	case 1:
    		bt1->etat = plein;
    		bt1->image = "images_coffrets/coffre_plein.jpg";

    		bt2->etat = vide;
    		bt2->image = "images_coffrets/coffre_vide.jpg";

    		bt3->etat = vide;
    		bt3->image = "images_coffrets/coffre_vide.jpg";
    		break;
    	case 2:
    		bt1->etat = vide;
    		bt1->image = "images_coffrets/coffre_vide.jpg";

    		bt2->etat = plein;
    		bt2->image = "images_coffrets/coffre_plein.jpg";

    		bt3->etat = vide;
    		bt3->image = "images_coffrets/coffre_vide.jpg";
    		break;
    	case 3:
    		bt1->etat = vide;
    		bt1->image = "images_coffrets/coffre_vide.jpg";

    		bt2->etat = vide;
    		bt2->image = "images_coffrets/coffre_vide.jpg";

    		bt3->etat = plein;
    		bt3->image = "images_coffrets/coffre_plein.jpg";
    		break;
    	default:
    		bt1->etat = plein;
    		bt1->image = "images_coffrets/coffre_plein.jpg";

    		bt2->etat = vide;
    		bt2->image = "images_coffrets/coffre_vide.jpg";

    		bt3->etat = vide;
    		bt3->image = "images_coffrets/coffre_vide.jpg";
    		break;
    }
}

void click_recommencer(GtkWidget *pF, gpointer data){
	assert(pF!=NULL);

	Interface *interface = (Interface *)data;

	//reset de la manche
	interface->manche = 1;

	//reset des images des boutons
	gtk_button_set_image(GTK_BUTTON(interface->bt1->pBouton), reinitialiser_image());
	gtk_button_set_image(GTK_BUTTON(interface->bt2->pBouton), reinitialiser_image());
	gtk_button_set_image(GTK_BUTTON(interface->bt3->pBouton), reinitialiser_image());

	//reset de l'état des coffres
	aleatoire(interface->bt1, interface->bt2, interface->bt3);

	//reset du label
	gtk_label_set_text(GTK_LABEL(interface->pLabel), "Choisissez un coffre!");
}

void click_bouton1(GtkWidget *pF, gpointer data){
	assert(pF!=NULL);

	Interface *interface = (Interface *)data;

	//MANCHE 1
	if(interface->manche == 1){
		//mise à l'état grisé du bouton Recommencer
		gtk_widget_set_sensitive(interface->pRecommencer, FALSE);

		//incrémentation de la manche
		interface->manche++;

		//modification des images des boutons 2 et 3
		if(interface->bt2->etat == vide)
			gtk_button_set_image(GTK_BUTTON(interface->bt2->pBouton), charge_image_bouton(interface->bt2->image));
		
		else
			gtk_button_set_image(GTK_BUTTON(interface->bt3->pBouton), charge_image_bouton(interface->bt3->image));
	}

	//MANCHE 2
	else if(interface->manche == 2){
		if(interface->bt1->etat == plein){
			//incrémentation du nombre de victoires
			interface->nb_vict++;

			//modification du label
			gtk_label_set_text(GTK_LABEL(interface->pLabel), "Gagné");
		}

		else{
			//incrémentation du nombre de défaites
			interface->nb_def++;

			//modification du label
			gtk_label_set_text(GTK_LABEL(interface->pLabel), "Perdu");
		}

		//Affichage des changements
		gtk_widget_set_sensitive(interface->pRecommencer, TRUE);
		gtk_button_set_image(GTK_BUTTON(interface->bt1->pBouton), charge_image_bouton(interface->bt1->image));
		scores_mise_a_jour(interface->pScore, interface->nb_vict, interface->nb_def);

		//incrémentation de la manche
		interface->manche++;
	}
}

void click_bouton2(GtkWidget *pF, gpointer data){
	assert(pF!=NULL);

	Interface *interface = (Interface *)data;

	//MANCHE 1
	if(interface->manche == 1){
		//mise à l'état grisé du bouton Recommencer
		gtk_widget_set_sensitive(interface->pRecommencer, FALSE);

		//incrémentation de la manche
		interface->manche++;

		//modification des images des boutons 1 et 3
		if(interface->bt1->etat == vide)
			gtk_button_set_image(GTK_BUTTON(interface->bt1->pBouton), charge_image_bouton(interface->bt1->image));
		
		else
			gtk_button_set_image(GTK_BUTTON(interface->bt3->pBouton), charge_image_bouton(interface->bt3->image));
		
	}

	//MANCHE 2
	else if(interface->manche == 2){
		if(interface->bt2->etat == plein){
			//incrémentation du nombre de victoires
			interface->nb_vict++;

			//modification du label
			gtk_label_set_text(GTK_LABEL(interface->pLabel), "Gagné");
		}

		else{
			//incrémentation du nombre de défaites
			interface->nb_def++;

			//modification du label
			gtk_label_set_text(GTK_LABEL(interface->pLabel), "Perdu");
		}

		//Affichage des changements
		gtk_widget_set_sensitive(interface->pRecommencer, TRUE);
		gtk_button_set_image(GTK_BUTTON(interface->bt2->pBouton), charge_image_bouton(interface->bt2->image));
		scores_mise_a_jour(interface->pScore, interface->nb_vict, interface->nb_def);

		//incrémentation de la manche
		interface->manche++;
	}
}

void click_bouton3(GtkWidget *pF, gpointer data){
	assert(pF!=NULL);

	Interface *interface = (Interface *)data;

	//MANCHE 1
	if(interface->manche == 1){
		//mise à l'état grisé du bouton Recommencer
		gtk_widget_set_sensitive(interface->pRecommencer, FALSE);

		//incrémentation de la manche
		interface->manche++;

		//modification des images des boutons 1 et 2
		if(interface->bt1->etat == vide)
			gtk_button_set_image(GTK_BUTTON(interface->bt1->pBouton), charge_image_bouton(interface->bt1->image));

		else
			gtk_button_set_image(GTK_BUTTON(interface->bt2->pBouton), charge_image_bouton(interface->bt2->image));
	}

	//MANCHE 2
	else if(interface->manche == 2){
		if(interface->bt3->etat == plein){
			//incrémentation du nombre de victoires
			interface->nb_vict++;

			//modification du label
			gtk_label_set_text(GTK_LABEL(interface->pLabel), "Gagné");
		}

		else{
			//incrémentation du nombre de défaites
			interface->nb_def++;

			//modification du label
			gtk_label_set_text(GTK_LABEL(interface->pLabel), "Perdu");
		}
		
		//Affichage des changements
		gtk_widget_set_sensitive(interface->pRecommencer, TRUE);
		gtk_button_set_image(GTK_BUTTON(interface->bt3->pBouton), charge_image_bouton(interface->bt3->image));
		scores_mise_a_jour(interface->pScore, interface->nb_vict, interface->nb_def);

		//incrémentation de la manche
		interface->manche++;
	}
}
