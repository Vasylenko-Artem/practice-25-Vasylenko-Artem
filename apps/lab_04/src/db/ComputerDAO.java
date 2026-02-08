package db;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ComputerDAO {

    public void addComputer(String name, String cpuType, double cpuFreq, int ram, int hdd, String video, String sound) throws SQLException {
        String sql = "INSERT INTO computers (name, cpu_type, cpu_frequency, ram_gb, hdd_gb, video_card, sound_card) VALUES (?, ?, ?, ?, ?, ?, ?)";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, name);
            stmt.setString(2, cpuType);
            stmt.setDouble(3, cpuFreq);
            stmt.setInt(4, ram);
            stmt.setInt(5, hdd);
            stmt.setString(6, video);
            stmt.setString(7, sound);
            stmt.executeUpdate();
        }
    }

    public void deleteComputer(int id) throws SQLException {
        String sql = "DELETE FROM computers WHERE id = ?";
        try (Connection conn = DBConnection.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, id);
            int rows = stmt.executeUpdate();
            if (rows == 0) {
                System.out.println("Computer with this id was not found");
            }
        }
    }

    public List<String> getAllComputersWithId() throws SQLException {
        List<String> list = new ArrayList<>();
        String sql = "SELECT id, name, cpu_type, cpu_frequency, ram_gb FROM computers";
        try (Connection conn = DBConnection.getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
            while (rs.next()) {
                list.add(rs.getInt("id") + ": " +
                         rs.getString("name") +
                         " | CPU: " + rs.getString("cpu_type") + " " + rs.getDouble("cpu_frequency") + "GHz" +
                         " | RAM: " + rs.getInt("ram_gb") + "GB");
            }
        }
        return list;
    }
}
