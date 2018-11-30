#########
#
# Programmes socket sans bibliotheques
#
#########


# For Linux
LD_FLAGS =

all: client serveur

client: client.c 
	gcc client.c -o client   $(LD_FLAGS)

serveur: serveur.c 
	gcc serveur.c -o serveur  $(LD_FLAGS)

clean:
	rm *~ ; rm -i \#* ; rm *.o; \
        rm client ; rm serveur
