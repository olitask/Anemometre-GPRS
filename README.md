# Anemometre-GPRS
Un anémomètre autonome en énergie, connecté , qui envoie ses données en GPRS sur un serveur  mysql

L'anémomètre -girouette utilisé est un modèle disponible chez les revendeurs chinois. Alimentés en 7-24VoltDC, ils convertissent la vitesse du vent ou l'orientation de la girouette par rapport au nord en une tension continue proportionnelle à la vitesse ou l'angle.

Un arduino et un module sim800L envoient les données sur un serveur mysql

Un raspberry pi avec nginx, php et mysql receptionnent les données

Deux panneaux solaires rechargent les batteries Li-ion.
