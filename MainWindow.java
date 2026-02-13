import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File; // Nécessaire pour manipuler le fichier sélectionné

public class MainWindow extends JFrame {
    private JTextArea textArea;
    private JTextField textField;
    private Client client;

    private Action searchAction;
    private Action playAction;
    private Action exitAction;
    private Action addFileAction; // Nouvelle action pour l'ajout de fichier

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

        // --- Barre d'Outils ---
        JToolBar toolBar = new JToolBar();
        toolBar.add(addFileAction); // Ajout à la barre d'outils
        toolBar.add(searchAction);
        toolBar.add(playAction);
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
        // Nouvelle action : Sélection de fichier
        addFileAction = new AbstractAction("AJOUTER") {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                // On ouvre la boîte de dialogue
                int returnVal = chooser.showOpenDialog(MainWindow.this);
                
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    File file = chooser.getSelectedFile();
                    // On met à jour le champ de texte avec le nom du fichier
                    textField.setText(file.getName());
                    textArea.append("Fichier sélectionné : " + file.getAbsolutePath() + "\n");
                }
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