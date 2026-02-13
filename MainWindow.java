import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MainWindow extends JFrame {
    private JTextArea textArea;    // Affichage des réponses
    private JTextField textField; // Saisie du nom de l'objet
    private Client client;        // La logique réseau

    // Définition des Actions réutilisables
    private Action searchAction;
    private Action playAction;
    private Action exitAction;

    public MainWindow() {
        // Configuration spécifique pour MacOSX
        System.setProperty("apple.laf.useScreenMenuBar", "true");

        // 1. Initialisation du réseau
        try {
            client = new Client("localhost", 3331);
        } catch (Exception e) {
            System.err.println("Erreur: Serveur C++ introuvable !");
        }

        // 2. Initialisation des Actions
        initializeActions();

        // 3. Création de l'interface
        textArea = new JTextArea(15, 50);
        textArea.setEditable(false);
        textField = new JTextField(20);

        // --- Barre de Menus ---
        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("Fichier");
        menu.add(new JMenuItem(searchAction));
        menu.add(new JMenuItem(playAction));
        menu.addSeparator();
        menu.add(new JMenuItem(exitAction));
        menuBar.add(menu);
        setJMenuBar(menuBar);

        // --- Barre d'Outils (Zone NORD) ---
        JToolBar toolBar = new JToolBar();
        toolBar.add(searchAction);
        toolBar.add(playAction);
        toolBar.addSeparator();
        toolBar.add(exitAction);
        add(toolBar, BorderLayout.NORTH);

        // --- Panneau de contrôle (Zone SUD) ---
        JPanel panel = new JPanel();
        panel.add(new JLabel("Nom:"));
        panel.add(textField);
        // On peut aussi ajouter les actions sous forme de boutons ici
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
     * Initialise les actions avec leur nom et leur comportement (actionPerformed)
     */
    private void initializeActions() {
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

    // Méthode pour envoyer la commande et afficher la réponse
    private void envoyerCommande(String command) {
        if (client == null) {
            textArea.append("Erreur: Client non connecté\n");
            return;
        }
        String response = client.send(command);
        textArea.append("Envoi: " + command + "\n");
        textArea.append("Réponse: " + response + "\n\n");
    }

    public static void main(String[] args) {
        // Il est préférable de lancer l'interface Swing dans l'Event Dispatch Thread
        SwingUtilities.invokeLater(() -> {
            new MainWindow();
        });
    }
}