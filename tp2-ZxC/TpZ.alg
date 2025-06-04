
  /*---------------------------------------------------------------------------*/
  /*                     TP Z Khawarizm : BST SEARCH                           */
  /*                                                                           */
  /*                             Developed by :                                */
  /*                        Cheballah Tinhinane  G04                           */
  /*                            Kellil Douaa  G05                              */
  /*                                                                           */
  /*                Supervised by : Prof.Dr Zegour D.Eddine                    */
  /*---------------------------------------------------------------------------*/
  /*------------------------- Variables Declaration ---------------------------*/
   SOIT
       F UN FICHIER DE ( CHAINE ) BUFFER S ;
       Bst1 , Bst2 , Bst3 DES ARB DE ( CHAINE ) ;
       Snode UNE STRUCTURE ( CHAINE ) ;
       I , J , K , Count_whole_bst1 , Count_whole_bst2 , Count_whole_bst3 , Choice : ENTIER ;
       Word , Word1 , Word2 , X , C , Y , Z , Temp : CHAINE ;
      /*---------------------------------------------------------------------------*/
      /*--------------------------- Procedures Headers ----------------------------*/
       Research2 UNE ACTION ;
       Research UNE ACTION ;
       Construct_bst1 UNE ACTION ;
       Rotation_bst UNE ACTION ;
       Right_rotation UNE ACTION ;
       Left_rotation UNE ACTION ;
       Insert_node UNE ACTION ;
       Display_bst UNE ACTION ;
       Inorder UNE ACTION ;
       Construct_bst3 UNE ACTION ;
       Construct_bst2 UNE ACTION ;
       Search_in_bst1 UNE ACTION ;
       Search_in_bst2 UNE ACTION ;
       Search_in_bst3 UNE ACTION ;
       Word_search UNE ACTION ;
       Rangquery UNE ACTION ;
       Process UNE ACTION ;
       Nextinorder UNE ACTION ;
       Smallestnode UNE ACTION ;
       Menu UNE ACTION ;
       Resault UN POINTEUR VERS ARB DE ( CHAINE ) ;
       Process2 UNE ACTION ;
       Postorder UNE ACTION ;
       Freetree UNE ACTION ;
      /*---------------------------------------------------------------------------*/
      /*------------------------------ Main Program -------------------------------*/
   DEBUT
       APPEL Menu ( 0 ) ;
       LIRE ( Choice ) ;
       TQ Choice <> 6
           SI Choice = 1
               ECRIRE ( ' ' ) ;
               ECRIRE ( 'Please enter x : ' ) ;
               LIRE ( X ) ;
               ECRIRE ( 'Please enter y : ' ) ;
               LIRE ( Y ) ;
               ECRIRE ( 'Please enter z : ' ) ;
               LIRE ( Z ) ;
               OUVRIR ( F , 'F2.z' , 'N' ) ;
               Count_whole_bst1 := 0 ;
               Count_whole_bst2 := 0 ;
               Count_whole_bst3 := 0 ;
               POUR I := 1 , 15
                   J := ALEANOMBRE ( 5 ) ;
                   SI J = 0 :
                       Word := X + ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
                   SINON
                       SI J = 1 :
                           Word := Y + ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
                       SINON
                           SI J = 2 :
                               Word := Z + ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
                           SINON
                               Word := ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
                           FSI ;
                       FSI ;
                   FSI ;
                   INIT_STRUCT ( S , [ Word ] ) ;
                   ECRIRESEQ ( F , S ) ;
                   Word := STRUCT ( S , 1 ) ;
                   APPEL Construct_bst1 ( Bst1 , Word , Count_whole_bst1 ) ;
                   APPEL Construct_bst2 ( Bst2 , Word , Count_whole_bst2 ) ;
                   APPEL Construct_bst3 ( Bst3 , Word , Count_whole_bst3 ) ;
               FPOUR ;
               FERMER ( F ) ;
               ECRIRE ( ' The triplet is generated successfully !' ) ;
               ECRIRE ( ' ' ) ;
               APPEL Menu ( 0 ) ;
               LIRE ( Choice ) ;
           FSI ;
           SI Choice = 2
               ECRIRE ( ' ' ) ;
               SI ( Bst1 = NIL ) OU ( Bst2 = NIL ) OU ( Bst3 = NIL )
                   ECRIRE ( ' Please generate the trees first ' ) ;
                   ECRIRE ( ' ' ) ;
               SINON
                   ECRIRE ( 'The number of words starting with x or y or z in BST1 is  ' , Count_whole_bst1 ) ;
                   APPEL Display_bst ( Bst1 ) ;
                   ECRIRE ( ' ' ) ;
                   ECRIRE ( 'The number of words starting with x or y or z in BST2 is  ' , Count_whole_bst2 ) ;
                   APPEL Display_bst ( Bst2 ) ;
                   ECRIRE ( ' ' ) ;
                   ECRIRE ( 'The number of words starting with x or y or z in BST3 is  ' , Count_whole_bst3 ) ;
                   APPEL Display_bst ( Bst3 ) ;
                   ECRIRE ( ' ' ) ;
                   ECRIRE ( ' ' ) ;
               FSI ;
               APPEL Menu ( 0 ) ;
               LIRE ( Choice ) ;
           FSI ;
           SI Choice = 3
               SI ( Bst1 = NIL ) OU ( Bst2 = NIL ) OU ( Bst3 = NIL )
                   ECRIRE ( ' ' ) ;
                   ECRIRE ( ' Please generate the trees first ' ) ;
                   ECRIRE ( ' ' ) ;
               SINON
                   ECRIRE ( ' ' ) ;
                   ECRIRE ( '*-*-*-*-*-*-*-*INORDER Traversal BST1*-*-*-*-*-*-*-*' ) ;
                   APPEL Inorder ( Bst1 ) ;
                   ECRIRE ( ' ' ) ;
                   ECRIRE ( '*-*-*-*-*-*-*-*INORDER Traversal BST2*-*-*-*-*-*-*-*' ) ;
                   APPEL Inorder ( Bst2 ) ;
                   ECRIRE ( '*-*-*-*-*-*-*-*INORDER Traversal BST3*-*-*-*-*-*-*-*' ) ;
                   APPEL Inorder ( Bst3 ) ;
                   ECRIRE ( ' ' ) ;
               FSI ;
               APPEL Menu ( 0 ) ;
               LIRE ( Choice ) ;
           FSI ;
           SI Choice = 4
               SI ( Bst1 = NIL ) OU ( Bst2 = NIL ) OU ( Bst3 = NIL )
                   ECRIRE ( ' ' ) ;
                   ECRIRE ( ' Please generate the trees first ' ) ;
                   ECRIRE ( ' ' ) ;
               SINON
                   ECRIRE ( 'Please enter the word you want to search for' ) ;
                   LIRE ( Word ) ;
                   APPEL Word_search ( Word ) ;
                   ECRIRE ( ' ' ) ;
               FSI ;
               APPEL Menu ( 0 ) ;
               LIRE ( Choice ) ;
           FSI ;
           SI Choice = 5
               ;
               SI ( Bst1 = NIL ) OU ( Bst2 = NIL ) OU ( Bst3 = NIL )
                   ECRIRE ( ' ' ) ;
                   ECRIRE ( ' Please generate the trees first ' ) ;
                   ECRIRE ( ' ' ) ;
               SINON
                   ECRIRE ( 'Please enter word1: ' ) ;
                   LIRE ( Word1 ) ;
                   ECRIRE ( 'Please enter word2: ' ) ;
                   LIRE ( Word2 ) ;
                   ECRIRE ( 'The result in the triplet (BST1, BST2, BST3) is' ) ;
                  /*We get the same display for each bst search 
        so it's enough to display only one*/
                   APPEL Rangquery ( Bst1 , Word1 , Word2 ) ;
                   ECRIRE ( ' ' ) ;
               FSI ;
               APPEL Menu ( 0 ) ;
               LIRE ( Choice ) ;
           FSI ;
           SI ( Choice < 1 ) OU ( Choice > 6 )
               ECRIRE ( ' ' ) ;
               ECRIRE ( ' Please choose a valid option ' ) ;
               ECRIRE ( ' ' ) ;
               APPEL Menu ( 0 ) ;
               LIRE ( Choice ) ;
           FSI ;
       FTQ ;
       APPEL Freetree ( Bst1 , Bst2 , Bst3 ) ;
   FIN
  /*-------------------------- End of Main Program ----------------------------*/
  /*---------------------------------------------------------------------------*/
  /*---------------------------------------------------------------------------*/
  /*                             Research in BST                               */
  /*---------------------------------------------------------------------------*/
   ACTION Research ( Root , P , Parent , Word ) ;
   SOIENT
       P , Root , Parent DES ARB DE ( CHAINE ) ;
       Word UNE CHAINE ;
       Found UN BOOLEEN ;
   DEBUT
       Found := FAUX ;
       Parent := NIL ;
       P := Root ;
       TQ ( P <> NIL ) ET ( NON Found )
           SI STRUCT ( INFO ( P ) , 1 ) = Word
               ;
               Found := VRAI ;
           SINON
               Parent := P ;
               SI Word > STRUCT ( INFO ( P ) , 1 )
                   P := FD ( P ) ;
               SINON
                   P := FG ( P ) ;
               FSI
           FSI
       FTQ
   FIN
  /*---------------------------------------------------------------------------*/
  /*                             Construct BST1                                */
  /*---------------------------------------------------------------------------*/
   ACTION Construct_bst1 ( Root , Word , Count_whole_bst )
   SOIENT
       Root , P , Q , Parent DES POINTEUR VERS ARB DE ( CHAINE ) ;
       Word UNE CHAINE ;
       Count_whole_bst UN ENTIER ;
   DEBUT
       APPEL Research ( Root , P , Parent , Word ) ;
       SI ( P = NIL )
           CREERNOEUD ( Q ) ;
           INIT_STRUCT ( Snode , [ Word ] ) ;
           AFF_INFO ( Q , Snode ) ;
           SI Parent = NIL
               SI ( CARACT ( Word , 1 ) = CARACT ( X , 1 ) ) OU ( CARACT ( Word , 1 ) = CARACT ( Y , 1 ) ) OU ( CARACT
               ( Word , 1 ) = CARACT ( Z , 1 ) )
                   Count_whole_bst := Count_whole_bst + 1 ;
               FSI ;
               Root := Q ;
           SINON
               APPEL Insert_node ( Q , Parent ) ;
               SI ( CARACT ( Word , 1 ) = CARACT ( X , 1 ) ) OU ( CARACT ( Word , 1 ) = CARACT ( Y , 1 ) ) OU ( CARACT
               ( Word , 1 ) = CARACT ( Z , 1 ) )
                   Count_whole_bst := Count_whole_bst + 1 ;
                   APPEL Rotation_bst ( Q , Parent ) ;
                   Root := Q ;
               FSI
           FSI
       FSI ;
   FIN
  /*---------------------------------------------------------------------------*/
  /*                             Construct BST2                                */
  /*---------------------------------------------------------------------------*/
   ACTION Construct_bst2 ( Root , Word , Count_whole_bst2 )
   SOIENT
       Root , P , Q , Parent DES POINTEUR VERS ARB DE ( CHAINE ) ;
       Word UNE CHAINE ;
       Lengthpath UN ENTIER ;
       Count_whole_bst2 UN ENTIER ;
       Demilengthpath UN ENTIER ;
   DEBUT
       APPEL Research2 ( Root , P , Parent , Word , Lengthpath ) ;
       SI ( P = NIL )
           CREERNOEUD ( Q ) ;
           INIT_STRUCT ( Snode , [ Word ] ) ;
           AFF_INFO ( Q , Snode ) ;
           SI Parent = NIL
               SI ( CARACT ( Word , 1 ) = CARACT ( X , 1 ) ) OU ( CARACT ( Word , 1 ) = CARACT ( Y , 1 ) ) OU ( CARACT
               ( Word , 1 ) = CARACT ( Z , 1 ) )
                   Count_whole_bst2 := Count_whole_bst2 + 1
               FSI ;
               Root := Q ;
           SINON
               APPEL Insert_node ( Q , Parent ) ;
               SI ( CARACT ( Word , 1 ) = CARACT ( X , 1 ) ) OU ( CARACT ( Word , 1 ) = CARACT ( Y , 1 ) ) OU ( CARACT
               ( Word , 1 ) = CARACT ( Z , 1 ) )
                   Count_whole_bst2 := Count_whole_bst2 + 1 ;
                   Demilengthpath := Lengthpath / 2 ;
                   POUR K := 1 , Demilengthpath
                       APPEL Rotation_bst ( Q , Parent ) ;
                       Parent := PERE ( Q ) ;
                       SI PERE ( Q ) = NIL
                           Root := Q ;
                       FSI ;
                   FPOUR
               FSI
           FSI
       FSI
   FIN
  /*---------------------------------------------------------------------------*/
  /*                             Construct BST3                                */
  /*---------------------------------------------------------------------------*/
   ACTION Construct_bst3 ( Root , Word , Count_whole_bst )
   SOIENT
       Root , P , Q , Parent DES POINTEUR VERS ARB DE ( CHAINE ) ;
       Word UNE CHAINE ;
       Count_whole_bst UN ENTIER ;
   DEBUT
       APPEL Research ( Root , P , Parent , Word ) ;
       SI ( P = NIL )
           CREERNOEUD ( Q ) ;
           INIT_STRUCT ( Snode , [ Word ] ) ;
           AFF_INFO ( Q , Snode ) ;
           SI Parent = NIL
               SI ( CARACT ( Word , 1 ) = CARACT ( X , 1 ) ) OU ( CARACT ( Word , 1 ) = CARACT ( Y , 1 ) ) OU ( CARACT
               ( Word , 1 ) = CARACT ( Z , 1 ) )
                   Count_whole_bst := Count_whole_bst + 1 ;
               FSI ;
               Root := Q ;
           SINON
               APPEL Insert_node ( Q , Parent ) ;
               SI ( CARACT ( Word , 1 ) <> CARACT ( X , 1 ) ) ET ( CARACT ( Word , 1 ) <> CARACT ( Y , 1 ) ) ET (
               CARACT ( Word , 1 ) <> CARACT ( Z , 1 ) )
                   APPEL Rotation_bst ( Q , Parent ) ;
                   Root := Q ;
               SINON
                   Count_whole_bst := Count_whole_bst + 1 ;
               FSI
           FSI
       FSI ;
   FIN
  /*---------------------------------------------------------------------------*/
  /*                          Research for BST2                                */
  /*---------------------------------------------------------------------------*/
   ACTION Research2 ( Root , P , Parent , Word , Lengthpath ) ;
   SOIENT
       P , Root , Parent DES ARB DE ( CHAINE ) ;
       Word UNE CHAINE ;
       Found UN BOOLEEN ;
       Lengthpath UN ENTIER ;
   DEBUT
       Found := FAUX ;
       Parent := NIL ;
       P := Root ;
       Lengthpath := 0 ;
       TQ ( P <> NIL ) ET ( NON Found )
           Lengthpath := Lengthpath + 1 ;
           SI STRUCT ( INFO ( P ) , 1 ) = Word
               ;
               Found := VRAI ;
           SINON
               Parent := P ;
               SI Word > STRUCT ( INFO ( P ) , 1 )
                   P := FD ( P ) ;
               SINON
                   P := FG ( P ) ;
               FSI
           FSI
       FTQ ;
       SI NON Found
           ;
           Lengthpath := Lengthpath + 1 ;
       FSI ;
   FIN
  /*---------------------------------------------------------------------------*/
  /*                             Rotation BST                                  */
  /*---------------------------------------------------------------------------*/
   ACTION Rotation_bst ( Q , Parent )
   SOIENT
       Q , Sub_tree , Grandparent , Parent DES POINTEUR VERS ARB DE ( CHAINE ) ;
   DEBUT
       TQ ( PERE ( Q ) <> NIL )
           Parent := PERE ( Q ) ;
           SI ( FG ( Parent ) = Q )
               APPEL Right_rotation ( Q , Parent ) ;
           SINON
               APPEL Left_rotation ( Q , Parent ) ;
           FSI
       FTQ
   FIN
  /*---------------------------------------------------------------------------*/
  /*                             Right rotation                                */
  /*---------------------------------------------------------------------------*/
   ACTION Right_rotation ( P , Father )
   SOIENT
       P , Father , Grandparent , Sub_tree DES POINTEUR VERS ARB DE ( CHAINE ) ;
   DEBUT
       Grandparent := PERE ( Father ) ;
       Sub_tree := FD ( P ) ;
       AFF_FD ( P , Father ) ;
       AFF_FG ( Father , Sub_tree ) ;
       SI ( Sub_tree <> NIL )
           AFF_PERE ( Sub_tree , Father ) ;
       FSI ;
       AFF_PERE ( Father , P ) ;
       AFF_PERE ( P , Grandparent ) ;
       SI ( Grandparent <> NIL )
           SI FG ( Grandparent ) = Father
               AFF_FG ( Grandparent , P ) ;
           SINON
               AFF_FD ( Grandparent , P ) ;
           FSI
       FSI
   FIN
  /*---------------------------------------------------------------------------*/
  /*                             Left rotation                                 */
  /*---------------------------------------------------------------------------*/
   ACTION Left_rotation ( P , Father )
   SOIENT
       P , Father , Grandparent , Sub_tree DES POINTEUR VERS ARB DE ( CHAINE ) ;
   DEBUT
       Grandparent := PERE ( Father ) ;
       Sub_tree := FG ( P ) ;
       AFF_FG ( P , Father ) ;
       AFF_FD ( Father , Sub_tree ) ;
       SI ( Sub_tree <> NIL )
           AFF_PERE ( Sub_tree , Father ) ;
       FSI ;
       AFF_PERE ( Father , P ) ;
       AFF_PERE ( P , Grandparent ) ;
       SI ( Grandparent <> NIL )
           SI FD ( Grandparent ) = Father
               AFF_FD ( Grandparent , P ) ;
           SINON
               AFF_FG ( Grandparent , P ) ;
           FSI
       FSI
   FIN
  /*---------------------------------------------------------------------------*/
  /*                             Insert new node                               */
  /*---------------------------------------------------------------------------*/
   ACTION Insert_node ( P , Father )
   SOIENT
       P , Temp , Father DES POINTEUR VERS ARB DE ( CHAINE ) ;
   DEBUT
       SI STRUCT ( INFO ( P ) , 1 ) < STRUCT ( INFO ( Father ) , 1 )
           AFF_FG ( Father , P ) ;
           AFF_PERE ( P , Father ) ;
       SINON
           AFF_FD ( Father , P ) ;
           AFF_PERE ( P , Father ) ;
       FSI
   FIN
  /*---------------------------------------------------------------------------*/
  /*                     Traverse and display the bst                          */
  /*---------------------------------------------------------------------------*/
   ACTION Display_bst ( R )
   SOIENT
       R , Current DES ARB DE ( CHAINE ) ;
       Queue UNE FILE DE ARB DE ( CHAINE ) ;
       Nb_of_nodes_xyz , Lvl , I , Nodes_in_current_level , Nodes_in_next_level : ENTIER ;
   DEBUT
       Lvl := 0 ;
       SI ( R = NIL )
           ECRIRE ( 'Arbre vide' ) ;
       FSI ;
       CREERFILE ( Queue ) ;
       ENFILER ( Queue , R ) ;
       Lvl := 0 ;
       Nb_of_nodes_xyz := 0 ;
       Nodes_in_current_level := 1 ;
       Nodes_in_next_level := 0 ;
       ECRIRE ( '*-*-*-*-*-*-*-*-*-* level ' , Lvl , '*-*-*-*-*-*-*-*-*-*' ) ;
       TQ ( NON FILEVIDE ( Queue ) )
           DEFILER ( Queue , Current ) ;
           SI ( CARACT ( ( STRUCT ( INFO ( Current ) , 1 ) ) , 1 ) = CARACT ( X , 1 ) ) OU ( CARACT ( ( STRUCT ( INFO
           ( Current ) , 1 ) ) , 1 ) = CARACT ( Y , 1 ) ) OU ( CARACT ( ( STRUCT ( INFO ( Current ) , 1 ) ) , 1 ) =
           CARACT ( Z , 1 ) )
               Nb_of_nodes_xyz := Nb_of_nodes_xyz + 1 ;
               ECRIRE ( STRUCT ( INFO ( Current ) , 1 ) ) ;
               ECRIRE ( ' ' ) ;
           FSI ;
           SI ( FG ( Current ) <> NIL )
               ENFILER ( Queue , FG ( Current ) ) ;
               Nodes_in_next_level := Nodes_in_next_level + 1 ;
           FSI ;
           SI ( FD ( Current ) <> NIL )
               ENFILER ( Queue , FD ( Current ) ) ;
               Nodes_in_next_level := Nodes_in_next_level + 1 ;
           FSI ;
           Nodes_in_current_level := Nodes_in_current_level - 1 ;
           SI ( Nodes_in_current_level = 0 )
               Lvl := Lvl + 1 ;
               ECRIRE ( 'The number of words starting with x or y or z at                this level is ' ,
               Nb_of_nodes_xyz ) ;
               ECRIRE ( ' ' ) ;
               Nb_of_nodes_xyz := 0 ;
               SI ( NON FILEVIDE ( Queue ) )
                   ECRIRE ( '*-*-*-*-*-*-*-*-*-* level ' , Lvl , '*-*-*-*-*-*-*-*-*-*' ) ;
               FSI ;
               Nodes_in_current_level := Nodes_in_next_level ;
               Nodes_in_next_level := 0 ;
           FSI ;
       FTQ ;
       ECRIRE ( 'Total depth is : ' , Lvl ) ;
   FIN
  /*---------------------------------------------------------------------------*/
  /*                             Inorder Traversal                             */
  /*---------------------------------------------------------------------------*/
   ACTION Inorder ( R ) ;
   SOIENT
       R UN ARB DE ( CHAINE ) ;
   DEBUT
       SI R <> NIL
           APPEL Inorder ( FG ( R ) ) ;
           ECRIRE ( STRUCT ( INFO ( R ) , 1 ) ) ;
           APPEL Inorder ( FD ( R ) ) ;
       FSI
   FIN
  /*---------------------------------------------------------------------------*/
  /*                             Search for a word                             */
  /*---------------------------------------------------------------------------*/
   ACTION Word_search ( Word ) ;
   SOIT
       Word UNE CHAINE ;
   DEBUT
       SI ( ( CARACT ( Word , 1 ) = CARACT ( X , 1 ) ) OU ( CARACT ( Word , 1 ) = CARACT ( Y , 1 ) ) OU ( CARACT (
       Word , 1 ) = CARACT ( Z , 1 ) ) )
           APPEL Search_in_bst1 ( Bst1 , Word ) ;
       SINON
           SI ( CARACT ( Word , 1 ) > CARACT ( X , 1 ) ) OU ( CARACT ( Word , 1 ) > CARACT ( Y , 1 ) ) OU ( CARACT (
           Word , 1 ) > CARACT ( Z , 1 ) )
               APPEL Search_in_bst2 ( Bst2 , Word ) ;
           SINON
               APPEL Search_in_bst3 ( Bst3 , Word ) ;
           FSI
       FSI
   FIN
  /*---------------------------------------------------------------------------*/
  /*                        Search for a word in BST1                          */
  /*---------------------------------------------------------------------------*/
   ACTION Search_in_bst1 ( Bst , Word ) ;
   SOIENT
       P , Bst DES ARB DE ( CHAINE ) ;
       Found , Stop UN BOOLEEN ;
       Word_p , Word DES CHAINE ;
   DEBUT
       Found := FAUX ;
       Stop := FAUX ;
       P := Bst ;
       TQ ( NON Found ) ET ( NON Stop ) ET ( P <> NIL )
           SI STRUCT ( INFO ( P ) , 1 ) = Word
               Found := VRAI ;
           SINON
               SI Word > STRUCT ( INFO ( P ) , 1 )
                   P := FD ( P ) ;
                   SI ( P <> NIL )
                       Word_p := STRUCT ( INFO ( P ) , 1 ) ;
                       SI ( CARACT ( Word_p , 1 ) <> CARACT ( X , 1 ) ) ET ( CARACT ( Word_p , 1 ) <> CARACT ( Y , 1 )
                       ) ET ( CARACT ( Word_p , 1 ) <> CARACT ( Z , 1 ) )
                           Stop := VRAI ;
                       FSI
                   FSI
               SINON
                   P := FG ( P ) ;
                   SI ( P <> NIL )
                       Word_p := STRUCT ( INFO ( P ) , 1 ) ;
                       SI ( CARACT ( Word_p , 1 ) <> CARACT ( X , 1 ) ) ET ( CARACT ( Word_p , 1 ) <> CARACT ( Y , 1 )
                       ) ET ( CARACT ( Word_p , 1 ) <> CARACT ( Z , 1 ) )
                           Stop := VRAI ;
                       FSI
                   FSI
               FSI
           FSI ;
       FTQ ;
       SI ( Found )
           ECRIRE ( 'Found in BST1' ) ;
       SINON
           ECRIRE ( 'Not found in BST1' ) ;
       FSI ;
   FIN
  /*---------------------------------------------------------------------------*/
  /*                        Search for a word in BST2                          */
  /*---------------------------------------------------------------------------*/
   ACTION Search_in_bst2 ( Bst , Word ) ;
   SOIENT
       P , Bst DES ARB DE ( CHAINE ) ;
       Found , Stop UN BOOLEEN ;
       Word_p , Word DES CHAINE ;
   DEBUT
       Found := FAUX ;
       Stop := FAUX ;
       P := Bst ;
       TQ ( NON Found ) ET ( NON Stop )
           SI STRUCT ( INFO ( P ) , 1 ) = Word
               Found := VRAI ;
           SINON
               SI Word > STRUCT ( INFO ( P ) , 1 )
                   P := FD ( P ) ;
                   SI ( P = NIL )
                       Stop := VRAI ;
                   FSI
               SINON
                   P := FG ( P ) ;
                   SI ( P = NIL )
                       Stop := VRAI ;
                   FSI
               FSI
           FSI ;
       FTQ ;
       SI ( Found )
           ECRIRE ( 'Found in BST2' ) ;
       SINON
           ECRIRE ( 'Not found in BST2' ) ;
       FSI
   FIN
  /*---------------------------------------------------------------------------*/
  /*                        Search for a word in BST3                          */
  /*---------------------------------------------------------------------------*/
   ACTION Search_in_bst3 ( Bst , Word ) ;
   SOIENT
       P , Bst DES ARB DE ( CHAINE ) ;
       Found , Stop UN BOOLEEN ;
       Word_p , Word DES CHAINE ;
   DEBUT
       Found := FAUX ;
       Stop := FAUX ;
       P := Bst ;
       TQ ( NON Found ) ET ( NON Stop ) ET ( P <> NIL )
           SI STRUCT ( INFO ( P ) , 1 ) = Word
               Found := VRAI ;
           SINON
               SI Word > STRUCT ( INFO ( P ) , 1 )
                   P := FD ( P ) ;
                   SI ( P <> NIL )
                       Word_p := STRUCT ( INFO ( P ) , 1 ) ;
                       SI ( CARACT ( Word_p , 1 ) = CARACT ( X , 1 ) ) OU ( CARACT ( Word_p , 1 ) = CARACT ( Y , 1 ) )
                       OU ( CARACT ( Word_p , 1 ) = CARACT ( Z , 1 ) )
                           Stop := VRAI ;
                       FSI
                   FSI
               SINON
                   P := FG ( P ) ;
                   SI ( P <> NIL )
                       Word_p := STRUCT ( INFO ( P ) , 1 ) ;
                       SI ( CARACT ( Word_p , 1 ) = CARACT ( X , 1 ) ) OU ( CARACT ( Word_p , 1 ) = CARACT ( Y , 1 ) )
                       OU ( CARACT ( Word_p , 1 ) = CARACT ( Z , 1 ) )
                           Stop := VRAI ;
                       FSI
                   FSI
               FSI
           FSI ;
       FTQ ;
       SI ( Found )
           ECRIRE ( 'Found in BST3' ) ;
       SINON
           ECRIRE ( 'Not found in BST3' ) ;
       FSI ;
   FIN
  /*--------------------------------------------THE RANGE QUERY SECTION---------------------------------------*/
  /*---------------------------------------------------------------------------*/
  /*                        Find the smallest node                             */
  /*---------------------------------------------------------------------------*/
   ACTION Smallestnode ( Root , Word , Resault )
  /* get the small word greater then the word1 to start displaying */
   SOIENT
       Root , Current , Resault DES POINTEUR VERS ARB DE ( CHAINE ) ;
       Word UNE CHAINE ;
   DEBUT
       Current := Root ;
       Resault := NIL ;
       TQ ( Current <> NIL )
           SI STRUCT ( INFO ( Current ) , 1 ) >= Word
               Resault := Current ;
               Current := FG ( Current ) ;
           SINON
               Current := FD ( Current ) ;
           FSI
       FTQ
   FIN
  /*---------------------------------------------------------------------------*/
  /*                               Next inorder                                */
  /*---------------------------------------------------------------------------*/
   ACTION Nextinorder ( Current , Resault )
  /*get the node that is in the next order for given node */
   SOIENT
       Current , Node , Parentnode , Resault DES POINTEUR VERS ARB DE ( CHAINE ) ;
   DEBUT
       Resault := NIL ;
       SI ( Current = NIL )
           Resault := Resault
       SINON
           SI FD ( Current ) <> NIL
               Node := FD ( Current ) ;
               TQ ( FG ( Node ) <> NIL ) ET ( Node <> NIL )
                   Node := FG ( Node ) ;
               FTQ ;
               Resault := Node ;
           SINON
               Parentnode := PERE ( Current ) ;
               TQ ( Parentnode <> NIL )
                   SI Current = FG ( Parentnode )
                       Resault := Parentnode ;
                       Parentnode := NIL ;
                   SINON
                       Current := Parentnode ;
                       Parentnode := PERE ( Parentnode ) ;
                   FSI
               FTQ ;
           FSI ;
       FSI ;
   FIN
  /*---------------------------------------------------------------------------*/
  /*                  Process the node for range search                        */
  /*---------------------------------------------------------------------------*/
   ACTION Process ( Node )
  /*to pring the content of the node */
   SOIENT
       Node UN POINTEUR VERS ARB DE ( CHAINE ) ;
   DEBUT
       SI ( Node <> NIL )
           ECRIRE ( STRUCT ( INFO ( Node ) , 1 ) ) ;
       FSI
   FIN
  /*---------------------------------------------------------------------------*/
  /*                           Search by range in BST                          */
  /*---------------------------------------------------------------------------*/
   ACTION Rangquery ( Root , Word1 , Word2 )
  /*the procedure that generate the range of given interval  */
   SOIENT
       Root , Current2 , Nextnode DES POINTEUR VERS ARB DE ( CHAINE ) ;
       Word1 , Word2 UNE CHAINE ;
       Found UN ENTIER ;
       Word UNE CHAINE ;
   DEBUT
       SI Word1 < Word2
           Found := 0 ;
           APPEL Smallestnode ( Root , Word1 , Current2 ) ;
           TQ ( Current2 # NIL )
               Word := STRUCT ( INFO ( Current2 ) , 1 ) ;
               SI Word > Word2
                   Current2 := NIL ;
               SINON
                   Found := 1 ;
                   APPEL Process ( Current2 ) ;
                   APPEL Nextinorder ( Current2 , Nextnode ) ;
                   Current2 := Nextnode ;
                   SI Nextnode <> NIL
                       Current2 := Nextnode ;
                   SINON
                       Current2 := NIL ;
                   FSI
               FSI
           FTQ ;
           SI Found = 0
               ECRIRE ( 'No words found in the given range.' )
           FSI
       SINON
           ECRIRE ( 'Error: word1 must be less than word2 for range query. ' )
       FSI
   FIN
  /*-*-----------*-----------*----------*-----------*-----------*-----------*-----------*/
  /*---------------------------------------------------------------------------*/
  /*                  Process the node for freeing BST                         */
  /*---------------------------------------------------------------------------*/
   ACTION Process2 ( Root )
  /*to free one node */
   SOIENT
       Root , Ptr UN POINTEUR VERS ARB DE ( CHAINE ) ;
   DEBUT
       Ptr := Root ;
       LIBERERNOEUD ( Ptr ) ;
   FIN
  /*---------------------------------------------------------------------------*/
  /*                           Postorder Traversal                             */
  /*---------------------------------------------------------------------------*/
   ACTION Postorder ( Root )
  /*visite all the nodes of the tree and free them with postoder procedure*/
  /*we use postorder since it visite the children first then the parent and the root is the last one */
   SOIENT
       Root UN POINTEUR VERS ARB DE ( CHAINE ) ;
   DEBUT
       SI ( Root <> NIL )
           APPEL Postorder ( FG ( Root ) ) ;
           APPEL Postorder ( FD ( Root ) ) ;
           APPEL Process2 ( Root )
       FSI
   FIN
  /*---------------------------------------------------------------------------*/
  /*                               Free the BST                                */
  /*---------------------------------------------------------------------------*/
   ACTION Freetree ( Root1 , Root2 , Root3 )
  /*free the three trees */
   SOIENT
       Root1 , Root2 , Root3 DES POINTEUR VERS ARB DE ( CHAINE ) ;
   DEBUT
       APPEL Postorder ( Root1 ) ;
       APPEL Postorder ( Root2 ) ;
       APPEL Postorder ( Root3 ) ;
   FIN
  /*---------------------------------------------------------------------------*/
  /*                               Menu display                                */
  /*---------------------------------------------------------------------------*/
   ACTION Menu ( M )
   SOIENT
       M UN ENTIER ;
   DEBUT
       ECRIRE ( '+*+*+*+*+*+*+*+*+* M E N U +*+*+*+*+*+*+*+*+*' ) ;
       ECRIRE ( ' ' ) ;
       ECRIRE ( ' ' ) ;
       ECRIRE ( '  1. Generate BST1, BST2, and BST3' ) ;
       ECRIRE ( '  2. Display BST1, BST2, and BST3' ) ;
       ECRIRE ( '  3. Inorder Traversal BST1, BST2, and BST3' ) ;
       ECRIRE ( '  4. Search a word in the triplet (BST1, BST2, BST3)' ) ;
       ECRIRE ( '  5. Search for all words within a range in the triplet (BST1, BST2, BST3)' ) ;
       ECRIRE ( '  6. Exit' ) ;
       ECRIRE ( ' ' ) ;
       ECRIRE ( ' ' ) ;
       ECRIRE ( '   Please enter your choice --> ' ) ;
   FIN
  /*---------------------------------------------------------------------------*/
  /*----------------------------- End of Program ------------------------------*/