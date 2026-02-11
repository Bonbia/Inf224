import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MainWindow extends JFrame {
    private JTextArea textArea;
    private JButton searchButton, playButton, quitButton;

    public MainWindow() {
        // Configuration de la fenêtre
        setTitle("Télécommande Multimédia");
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        // Zone de texte avec scroll
        textArea = new JTextArea(10, 40);
        JScrollPane scrollPane = new JScrollPane(textArea);
        add(scrollPane, BorderLayout.CENTER);

        // Panneau des boutons
        JPanel buttonPanel = new JPanel();
        searchButton = new JButton("Rechercher");
        playButton = new JButton("Jouer");
        quitButton = new JButton("Quitter");

        buttonPanel.add(searchButton);
        buttonPanel.add(playButton);
        buttonPanel.add(quitButton);
        add(buttonPanel, BorderLayout.SOUTH);

        // Actions des boutons
        quitButton.addActionListener(e -> System.exit(0));
        
        pack(); // Ajuste la taille automatiquement
        setVisible(true);
    }

    public static void main(String[] args) {
        new MainWindow();
    }
}