# Documentation du Serveur Palwish

## Protocole réseau

Le serveur fonctionne sur TCP, port `8070` (défini par la macro `PORT`).

## Formats de messages

### Envois par le client

- **Mise à jour complète d'un joueur** :
  ```
  <user_id>/<x>/<y>/<life>/<type>\n
  ```
  - `user_id` : identifiant unique de l'utilisateur (fd côté serveur)
  - `x`, `y` : position du joueur (float)
  - `life` : points de vie (float)
  - `type` : type d'utilisateur (0 = joueur, autres valeurs possibles pour bots/objets)

- **Mise à jour de la vie uniquement** :
  ```
  <user_id>/<life>/<type>\n
  ```
  - `user_id` : identifiant unique de l'utilisateur
  - `life` : points de vie (float)
  - `type` : type d'utilisateur

### Envois par le serveur

- **Liste complète des utilisateurs** :
  ```
  <user_id>/<x>/<y>/<life>/<type>\n
  <user_id>/<x>/<y>/<life>/<type>\n
  ...
  ```
  Envoyé lors de la connexion ou sur demande.

- **Mise à jour d'un utilisateur** :
  ```
  <user_id>/<x>/<y>/<life>/<type>\n
  ```
  Envoyé à tous les clients quand un utilisateur est mis à jour.

## Routes / Actions réseau

### 1. Connexion d'un client

- Le client se connecte au serveur.
- Le serveur enregistre le client et lui envoie la liste de tous les utilisateurs connectés.

### 2. Mise à jour de l'état d'un joueur

- Le client envoie une mise à jour complète ou une mise à jour de vie uniquement.
- Le serveur met à jour l'utilisateur correspondant et diffuse les changements à tous les clients.

### 3. Déconnexion d'un client

- Si un client ferme la connexion, le serveur marque l'utilisateur comme mort (`life = 0`) et notifie les autres clients.

### 4. Synchronisation périodique

- Le serveur envoie régulièrement à tous les clients la liste des utilisateurs mis à jour.

### 5. Suppression d'un utilisateur

- Si `life` atteint 0, l'utilisateur est supprimé du serveur et la suppression est notifiée à tous les clients.

## Notes

- Toutes les communications sont en texte brut (UTF-8).
- Les champs sont séparés par `/`, chaque utilisateur sur une ligne.
- Le serveur ne gère pas de routes HTTP classiques, mais un protocole personnalisé sur TCP.

