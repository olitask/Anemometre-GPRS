 <?php
    // on se connecte à notre base
    $base = mysql_connect (localhost, utilisateurarduino, motdepassearduino);
    mysql_select_db ('data_anemo', $data_anemo) ;
  ?>
<html>
<head>
<title>Insertion de données dans la base</title>
</head>
<body>
<?php
$ori = $_GET["o"];
$vit = $_GET["v"];
$tmp = $_GET["t"];
//$pre = $_GET["p"];

// lancement de la requete
$sql = "INSERT INTO data_anemo.data_anemo1 (`id`, `Date`, `orientation`, `vitesse`, `temperature`) VALUES  ('',NOW() ,$ori , $vit, $tmp)";
// on insere le tuple (mysql_query) et au cas où, on écrira un petit message d'erreur si la requête ne se passe pas bien (or die)
mysql_query ($sql) or die ('Erreur SQL !'.$sql.'<br />'.mysql_error());

// on ferme la connexion à la base
mysql_close();
?>
qque chose vient d'être inseré dans la base.
<p>82.242.88.152/dossier/ <?php echo $_GET['o'] . ' ' . $_GET['v'] . ' ' . $_GET["t"] . ' ' ; ?> !</p>
</body>
</html>

