
<?php
// on se connecte à MySQL
$db = mysql_connect('localhost', 'utilisateurarduino', 'motdepassearduino');

// on sélectionne la base
mysql_select_db('data_anemo',$db);

// on crée la requête SQL
$sql = 'SELECT * FROM data_anemo1 ORDER BY Date DESC LIMIT 20';

// on envoie la requête
$req = mysql_query($sql) or die('Erreur SQL !<br>'.$sql.'<br>'.mysql_error());

// on fait une boucle qui va faire un tour pour chaque enregistrement
while($data = mysql_fetch_assoc($req))
    {
    // on affiche les informations de l'enregistrement en cours
    echo '<b>'.$data['id'].' '.$data['Date'].' UTC</b>    vitesse: '.$data['vitesse'].'km/h';
    echo ' <i>  orientation : '.$data['orientation'].' degrés</i><br>';
    }

// on ferme la connexion à mysql
mysql_close();
?> 


