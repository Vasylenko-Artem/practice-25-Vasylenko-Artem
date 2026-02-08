package gui;

import db.ComputerDAO;

import javax.swing.*;
import java.awt.*;
import java.sql.SQLException;

public class MainForm extends JFrame {

    private ComputerDAO dao = new ComputerDAO();
    private DefaultListModel<String> listModel = new DefaultListModel<>();
    private JList<String> computerList = new JList<>(listModel);

    public MainForm() {
        super("Computer Shop");

        JButton btnAdd = new JButton("Add");
        JButton btnRemove = new JButton("Remove");
        JButton btnRefresh = new JButton("Refresh");

        btnAdd.addActionListener(e -> new AddComputerForm(this, dao, this::refreshList));
        btnRemove.addActionListener(e -> removeSelectedComputer());
        btnRefresh.addActionListener(e -> refreshList());

        JPanel panel = new JPanel();
        panel.add(btnAdd);
        panel.add(btnRemove);
        panel.add(btnRefresh);

        computerList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

        add(panel, BorderLayout.NORTH);
        add(new JScrollPane(computerList), BorderLayout.CENTER);

        setDefaultCloseOperation(EXIT_ON_CLOSE);
        pack();
        setLocationRelativeTo(null);
        setVisible(true);

        refreshList();
    }

    public void refreshList() {
        try {
            listModel.clear();
            for (String s : dao.getAllComputersWithId()) {
                listModel.addElement(s);
            }
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage());
        }
    }

    private void removeSelectedComputer() {
        String selected = computerList.getSelectedValue();
        if (selected == null) {
            JOptionPane.showMessageDialog(this, "Please select a computer to remove");
            return;
        }
        int id = Integer.parseInt(selected.split(":")[0].trim());
        try {
            dao.deleteComputer(id);
            refreshList();
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error: " + e.getMessage());
        }
    }
}
