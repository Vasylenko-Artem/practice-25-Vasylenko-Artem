package gui;

import db.ComputerDAO;

import javax.swing.*;
import java.awt.*;
import java.sql.SQLException;

public class AddComputerForm extends JDialog {

    public AddComputerForm(JFrame parent, ComputerDAO dao, Runnable onSuccess) {
        super(parent, "Add Computer", true);
        setLayout(new GridLayout(8, 2));

        JTextField name = new JTextField();
        JTextField cpu = new JTextField();
        JTextField freq = new JTextField();
        JTextField ram = new JTextField();
        JTextField hdd = new JTextField();
        JTextField video = new JTextField();
        JTextField sound = new JTextField();

        add(new JLabel("Name:")); add(name);
        add(new JLabel("CPU Type:")); add(cpu);
        add(new JLabel("CPU Frequency (GHz):")); add(freq);
        add(new JLabel("RAM (GB):")); add(ram);
        add(new JLabel("HDD (GB):")); add(hdd);
        add(new JLabel("Video Card:")); add(video);
        add(new JLabel("Sound Card:")); add(sound);

        JButton btnAdd = new JButton("Add");
        btnAdd.addActionListener(e -> {
            try {
                dao.addComputer(
                        name.getText(),
                        cpu.getText(),
                        Double.parseDouble(freq.getText()),
                        Integer.parseInt(ram.getText()),
                        Integer.parseInt(hdd.getText()),
                        video.getText(),
                        sound.getText()
                );
                if (onSuccess != null) onSuccess.run(); // updating the list in MainForm
                dispose();
            } catch (SQLException ex) {
                JOptionPane.showMessageDialog(this, "Error: " + ex.getMessage());
            }
        });

        add(new JLabel());
        add(btnAdd);

        pack();
        setLocationRelativeTo(parent);
        setVisible(true);
    }
}
