import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File; // Nécessaire pour manipuler le fichier sélectionné
import javax.swing.filechooser.FileNameExtensionFilter;


public class MainWindow extends JFrame {
    private JTextArea textArea;
    private JTextField textField;
    private Client client;

    private Action searchAction;
    private Action playAction;
    private Action exitAction;
    private Action addFileAction; // Nouvelle action pour l'ajout de fichier
    private Action quitAction;

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

    private void initializeActions() {
        // Action pour l'ajout de fichier avec filtres
        addFileAction = new AbstractAction("AJOUTER") {
        @Override
        public void actionPerformed(ActionEvent e) {
        String desktopPath = System.getProperty("user.home") + File.separator + "Desktop";
        File desktopDir = new File(desktopPath);

        // Vérification de sécurité
        if (!desktopDir.exists() || !desktopDir.canRead()) {
            // Si le bureau est inaccessible, on se rabat sur le dossier "Home" de l'utilisateur
            desktopDir = new File(System.getProperty("user.home"));
            textArea.append("Note : Accès au Bureau refusé ou impossible. Redirection vers le dossier utilisateur.\n");
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

    private void envoyerCommande(String command) {
        if (client == null) return;
        String response = client.send(command);
        textArea.append("Envoi: " + command + "\n");
        textArea.append("Réponse: " + response + "\n\n");
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new MainWindow());
    }
}