
/**
 * @file MainWindow.java
 * @brief Interface graphique Swing pour le client multimédia
 * @author Telecom Paristech
 * @date 2024
 * 
 * Fournit une interface utilisateur complète pour interagir avec le serveur
 * de gestion multimédia. Inclut un menu, une barre d'outils, et des panneaux
 * pour l'affichage et le contrôle.
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File; // Nécessaire pour manipuler le fichier sélectionné
import javax.swing.filechooser.FileNameExtensionFilter;

/**
 * @class MainWindow
 * @brief Fenêtre principale du client multimédia avec interface Swing
 * 
 *        Crée une interface graphique complète incluant :
 *        - Menu fichier avec options de gestion
 *        - Barre d'outils avec boutons d'action
 *        - Zone de texte pour afficher les résultats et messages
 *        - Panneau de contrôle pour l'entrée utilisateur
 *        - Palette de sélection de fichiers pour ajouter des médias
 */
public class MainWindow extends JFrame {
    /**
     * @brief Zone de texte pour afficher les résultats et messages
     */
    private JTextArea textArea;

    /**
     * @brief Champ de texte pour entrer le nom d'un objet multimédia
     */
    private JTextField textField;

    /**
     * @brief Cliente TCP connectée au serveur multimédia
     */
    private Client client;

    /**
     * @brief Action pour rechercher un objet multimédia par nom
     */
    private Action searchAction;

    /**
     * @brief Action pour lire/jouer un objet multimédia
     */
    private Action playAction;

    /**
     * @brief Action pour quitter l'application
     */
    private Action exitAction;

    /**
     * @brief Action pour ajouter un nouveau fichier multimédia
     */
    private Action addFileAction;

    /**
     * @brief Action pour envoyer la commande QUIT au serveur
     */
    private Action quitAction;

    /**
     * @brief Constructeur - initialise et affiche la fenêtre principale
     * 
     *        Configure :
     *        - L'apparence (L&F)
     *        - La connexion au serveur
     *        - Les actions et leurs raccourcis
     *        - L'interface utilisateur (menus, barre d'outils, panneaux)
     * 
     *        Affiche également un message d'erreur si le serveur est indisponible
     */
    public MainWindow() {
        System.setProperty("apple.laf.useScreenMenuBar", "true");
        ImageIcon img = new ImageIcon("Logo.jpg");

        // Application de l'icône à la fenêtre
        this.setIconImage(img.getImage());
        try {
            client = new Client("localhost", 3331);
        } catch (Exception e) {
            System.err.println("Erreur: Serveur C++ introuvable !");
        }

        initializeActions();

        textArea = new JTextArea(15, 50);
        textArea.setEditable(false);
        textField = new JTextField(20);

        // --- Barre de Menus ---
        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("Fichier");
        menu.add(new JMenuItem(addFileAction)); // Ajout au menu
        menu.add(new JMenuItem(searchAction));
        menu.add(new JMenuItem(playAction));
        menu.addSeparator();
        menu.add(new JMenuItem(exitAction));
        menuBar.add(menu);
        setJMenuBar(menuBar);
        menu.add(new JMenuItem(quitAction)); // Dans le JMenu
        // --- Barre d'Outils ---
        JToolBar toolBar = new JToolBar();
        toolBar.add(addFileAction); // Ajout à la barre d'outils
        toolBar.add(searchAction);
        toolBar.add(playAction);
        toolBar.add(quitAction); // Ajout de quitAction à la barre d'outils
        add(toolBar, BorderLayout.NORTH);

        // --- Panneau de contrôle ---
        JPanel panel = new JPanel();
        panel.add(new JLabel("Nom:"));
        panel.add(textField);
        panel.add(new JButton(addFileAction)); // Bouton dédié dans le panel
        panel.add(new JButton(searchAction));
        panel.add(new JButton(playAction));

        add(new JScrollPane(textArea), BorderLayout.CENTER);
        add(panel, BorderLayout.SOUTH);

        setTitle("Client Multimedia");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        pack();
        setVisible(true);
    }

    /**
     * @brief Initialise toutes les actions de l'interface
     * 
     *        Crée et configure les actions pour :
     *        - Ajouter un fichier multimédias avec sélecteur de fichiers
     *        - Rechercher un objet par son nom
     *        - Lire/jouer un objet multimédia
     *        - Quitter l'application
     *        - Arrêtrer le serveur
     * 
     * @note Chaque action est liée à un bouton/menu et déclenche une logique
     *       spécifique
     */
    private void initializeActions() {
        // Action pour l'ajout de fichier avec filtres
        addFileAction = new AbstractAction("AJOUTER") {
            @Override
            public void actionPerformed(ActionEvent e) {
                String desktopPath = System.getProperty("user.home") + File.separator + "Desktop";
                File desktopDir = new File(desktopPath);

                // Vérification de sécurité
                if (!desktopDir.exists() || !desktopDir.canRead()) {
                    // Si le bureau est inaccessible, on se rabat sur le dossier "Home" de
                    // l'utilisateur
                    desktopDir = new File(System.getProperty("user.home"));
                    textArea.append(
                            "Note : Accès au Bureau refusé ou impossible. Redirection vers le dossier utilisateur.\n");
                }

                JFileChooser chooser = new JFileChooser(desktopDir);
                // ... (suite de votre configuration de filtres)

                // --- Configuration des filtres (comme précédemment) ---
                FileNameExtensionFilter imageFilter = new FileNameExtensionFilter(
                        "Images (JPG, PNG, GIF)", "jpg", "jpeg", "png", "gif");
                FileNameExtensionFilter videoFilter = new FileNameExtensionFilter(
                        "Vidéos (MP4, AVI, MKV)", "mp4", "avi", "mkv");

                chooser.addChoosableFileFilter(imageFilter);
                chooser.addChoosableFileFilter(videoFilter);
                chooser.setAcceptAllFileFilterUsed(false);
                chooser.setFileFilter(videoFilter);

                // 3. Affichage
                int returnVal = chooser.showOpenDialog(MainWindow.this);

                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    File file = chooser.getSelectedFile();
                    textField.setText(file.getName());
                    textArea.append("Fichier sélectionné : " + file.getAbsolutePath() + "\n");
                }
            }
        };

        quitAction = new AbstractAction("QUIT SERVEUR") {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Envoyer la commande au serveur C++
                envoyerCommande("QUIT");

                // Laisser un petit délai pour que le message parte, puis fermer Java
                Timer timer = new Timer(500, event -> System.exit(0));
                timer.setRepeats(false);
                timer.start();
            }
        };

        searchAction = new AbstractAction("SEARCH") {
            @Override
            public void actionPerformed(ActionEvent e) {
                String name = textField.getText();
                envoyerCommande("SEARCH " + name);
            }
        };

        playAction = new AbstractAction("PLAY") {
            @Override
            public void actionPerformed(ActionEvent e) {
                String name = textField.getText();
                envoyerCommande("PLAY " + name);
            }
        };

        exitAction = new AbstractAction("Quitter") {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        };
    }

    /**
     * @brief Envoie une commande au serveur et affiche le résultat
     * 
     *        Envoie une commande texte au serveur via le client TCP,
     *        puis affiche la commande et la réponse dans la zone de texte.
     * 
     * @param command La commande à envoyer au serveur
     * 
     * @note Peut être utilisée pour toute commande reconnue par le serveur
     */
    private void envoyerCommande(String command) {
        if (client == null)
            return;
        String response = client.send(command);
        textArea.append("Envoi: " + command + "\n");
        textArea.append("Réponse: " + response + "\n\n");
    }

    /**
     * @brief Point d'entrée de l'application
     * 
     *        Lance l'interface graphique sur le thread de distribution des
     *        événements Swing (EDT)
     *        pour assurer la sécurité des threads.
     * 
     * @param args Argument non utilisé
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new MainWindow());
    }
}