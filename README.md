# Anemometre-GPRS
Un anémomètre autonome en énergie, connecté , qui envoie ses données en GPRS sur un serveur  mysql

L'anémomètre -girouette utilisé est un modèle disponible chez les revendeurs chinois. Alimentés en 7-24VoltDC, ils convertissent la vitesse du vent ou l'orientation de la girouette par rapport au nord en une tension continue proportionnelle à la vitesse ou l'angle.
https://fr.aliexpress.com/item/0-5V-voltage-wind-speed-sensor-Voltage-output-Anemometer-360-degree-wind-speed-sensor/32371852577.html
https://fr.aliexpress.com/item/Wholesale-prices-4-20mA-Wind-direction-sensor-voltage-type-Wind-direction-sensor-anemometer-485/2033355563.html

Un arduino minipro 3.3V 8MHz et un module sim800L envoient les données sur un serveur mysql
https://fr.aliexpress.com/item/Free-Shipping-Smallest-SIM800L-GPRS-GSM-Module-MicroSIM-Card-Core-BOard-Quad-band-TTL-Serial-Port/32637906564.html

Un raspberry pi avec nginx, php et mysql receptionnent les données avec le script write.php 
La consultation se fait avec le script lire.php

Deux panneaux solaires rechargent les batteries Li-ion grace a deux TP4056.
https://fr.aliexpress.com/item/1pcs-TP4056-1A-Lipo-Battery-Charging-Board-Charger-Module-Lithium-Battery-DIY-Mini-USB-Port-for/32599144137.html
https://fr.aliexpress.com/item/5V-1-25W-Monocrystalline-Silicon-Epoxy-Solar-Panels-Module-kits-Mini-Solar-Cells-For-Charging-Cellphone/32819488562.html

