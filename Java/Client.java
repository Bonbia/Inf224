
/**
 * @file Client.java
 * @brief Client Java TCP pour communication avec serveur multimédia C++
 * @author Eric Lecolinet - Telecom Paristech
 * @date 2015-2024
 * 
 * Ce client établit une connexion socket avec un serveur C++ et permet
 * l'envoi de requêtes et la réception de réponses via un protocole texte.
 */

import java.io.*;
import java.net.*;

/**
 * @class Client
 * @brief Client TCP pour communication avec serveur multimédia
 * 
 *        Établit une connexion socket avec un serveur et gère l'envoi de
 *        requêtes
 *        texte ainsi que la réception de réponses. Supporte :
 *        - Connection réseau à distance ou locale
 *        - Envoi de requêtes texte
 *        - Réception de réponses texte
 *        - Gestion basique des erreurs
 * 
 * @note Le client bloque l'exécution si le serveur ne répond pas
 * @note Protocole : requêtes et réponses terminées par un saut de ligne
 */
public class Client {
  /**
   * @brief ID de sérialisation pour la classe
   */
  private static final long serialVersionUID = 1L;

  /**
   * @brief Hôte par défaut pour la connexion (localhost)
   */
  static final String DEFAULT_HOST = "localhost";

  /**
   * @brief Port par défaut pour la connexion
   */
  static final int DEFAULT_PORT = 3331;

  /**
   * @brief Socket de communication avec le serveur
   */
  private Socket sock;

  /**
   * @brief Lecteur pour les données reçues du serveur
   */
  private BufferedReader input;

  /**
   * @brief Écrivain pour les données envoyées au serveur
   */
  private BufferedWriter output;

  /**
   * @brief Point d'entrée du programme client
   * 
   *        Lit des requêtes depuis le terminal, les envoie au serveur,
   *        reçoit et affiche les réponses.
   * 
   *        Options de ligne de commande :
   *        - argv[0] : hôte du serveur (par défaut: localhost)
   *        - argv[1] : port du serveur (par défaut: 3331)
   * 
   * @param argv Arguments en ligne de commande [host] [port]
   * 
   * @note Le programme bloque si le serveur ne répond pas
   * @note Tapez les commandes et appuyez sur Entrée pour les envoyer
   */
  public static void main(String argv[]) {
    String host = DEFAULT_HOST;
    int port = DEFAULT_PORT;
    if (argv.length >= 1)
      host = argv[0];
    if (argv.length >= 2)
      port = Integer.parseInt(argv[1]);

    Client client = null;

    try {
      client = new Client(host, port);
    } catch (Exception e) {
      System.err.println("Client: Couldn't connect to " + host + ":" + port);
      System.exit(1);
    }

    System.out.println("Client connected to " + host + ":" + port);

    // pour lire depuis la console
    BufferedReader cin = new BufferedReader(new InputStreamReader(System.in));

    while (true) {
      System.out.print("Request: ");
      try {
        String request = cin.readLine();
        String response = client.send(request);
        System.out.println("Response: " + response);
      } catch (java.io.IOException e) {
        System.err.println("Client: IO error");
        return;
      }
    }
  }

  /**
   * @brief Constructeur - établit la connexion avec le serveur
   * 
   *        Crée une connexion socket avec le serveur spécifié et initialise
   *        les flux d'entrée/sortie pour la communication.
   * 
   * @param host Nom d'hôte ou adresse IP du serveur
   * @param port Port sur lequel le serveur écoute
   * 
   * @throws UnknownHostException si l'hôte n'est pas trouvable
   * @throws IOException          si la connexion échoue ou si les flux ne peuvent
   *                              pas être ouverts
   */
  public Client(String host, int port) throws UnknownHostException, IOException {
    try {
      sock = new java.net.Socket(host, port);
    } catch (java.net.UnknownHostException e) {
      System.err.println("Client: Couldn't find host " + host + ":" + port);
      throw e;
    } catch (java.io.IOException e) {
      System.err.println("Client: Couldn't reach host " + host + ":" + port);
      throw e;
    }

    try {
      input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
      output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
    } catch (java.io.IOException e) {
      System.err.println("Client: Couldn't open input or output streams");
      throw e;
    }
  }

  /**
   * @brief Envoie une requête au serveur et reçoit la réponse
   * 
   *        Cette méthode envoie une requête texte au serveur et attend une
   *        réponse.
   *        Elle bloque l'exécution jusqu'à la réception de la réponse.
   * 
   * @param request La requête texte à envoyer au serveur
   * 
   * @return La réponse reçue du serveur, ou null en cas d'erreur
   * 
   * @note Cette méthode bloque si le serveur ne répond pas
   * @note En cas d'erreur, null est retourné et un message d'erreur est affiché
   * @note Le protocole utilise des sauts de ligne comme séparateurs
   */
  public String send(String request) {
    // Envoyer la requete au serveur
    try {
      request += "\n"; // ajouter le separateur de lignes
      output.write(request, 0, request.length());
      output.flush();
    } catch (java.io.IOException e) {
      System.err.println("Client: Couldn't send message: " + e);
      return null;
    }

    // Recuperer le resultat envoye par le serveur
    try {
      return input.readLine();
    } catch (java.io.IOException e) {
      System.err.println("Client: Couldn't receive message: " + e);
      return null;
    }
  }
}
