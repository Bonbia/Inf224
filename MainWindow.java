import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MainWindow extends JFrame {
    private JTextArea textArea;    // Affichage des réponses
    private JTextField textField; // Saisie du nom de l'objet
    private Client client;        // La logique réseau

    public MainWindow() {
        // 1. Initialisation du réseau
        try {
            client = new Client("localhost", 3331);
        } catch (Exception e) {
            System.err.println("Erreur: Serveur C++ introuvable !");
        }

        // 2. Création de l'interface
        textArea = new JTextArea(10, 40);
        textField = new JTextField(20);
        JButton searchBtn = new JButton("SEARCH");
        JButton playBtn = new JButton("PLAY");

        // 3. Action pour le bouton SEARCH
        searchBtn.addActionListener(e -> {
            String name = textField.getText();
            envoyerCommande("SEARCH " + name);
        });

        // 4. Action pour le bouton PLAY
        playBtn.addActionListener(e -> {
            String name = textField.getText();
            envoyerCommande("PLAY " + name);
        });

        // Mise en page (Layout)
        JPanel panel = new JPanel();
        panel.add(new JLabel("Nom:"));
        panel.add(textField);
        panel.add(searchBtn);
        panel.add(playBtn);

        add(new JScrollPane(textArea), BorderLayout.CENTER);
        add(panel, BorderLayout.SOUTH);

        setDefaultCloseOperation(EXIT_ON_CLOSE);
        pack();
        setVisible(true);
    }

    // Méthode pour envoyer la commande et afficher la réponse
    private void envoyerCommande(String command) {
        if (client == null) return;
        String response = client.send(command); // On envoie au serveur C++
        textArea.append("Envoi: " + command + "\n");
        textArea.append("Réponse: " + response + "\n\n");
    }

    public static void main(String[] args) {
        new MainWindow();
    }
}