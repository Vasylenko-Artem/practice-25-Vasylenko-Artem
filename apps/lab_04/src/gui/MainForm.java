package gui;

import db.ComputerDAO;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.sql.SQLException;

public class MainForm extends JFrame {

    private ComputerDAO dao = new ComputerDAO();
    private JTextArea displayArea = new JTextArea(15, 40);

    public MainForm() {
        super("Computer Shop");

        JButton btnAdd = new JButton("Add Computer");
        JButton btnRefresh = new JButton("Refresh List");

        btnAdd.addActionListener((ActionEvent e) -> new AddComputerForm(this, dao));
        btnRefresh.addActionListener((ActionEvent e) -> refreshList());

        JPanel panel = new JPanel();
        panel.add(btnAdd);
        panel.add(btnRefresh);

        add(panel, BorderLayout.NORTH);
        add(new JScrollPane(displayArea), BorderLayout.CENTER);

        setDefaultCloseOperation(EXIT_ON_CLOSE);
        pack();
        setVisible(true);

        refreshList();
    }

    public void refreshList() {
        try {
            displayArea.setText(String.join("\n", dao.getAllComputers()));
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage());
        }
    }
}
