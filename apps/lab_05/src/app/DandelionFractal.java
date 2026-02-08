package app;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Point2D;

public class DandelionFractal extends JPanel {

    private int order; // Порядок фракталу
    private Point2D.Double P1, P2;

    public DandelionFractal(Point2D.Double P1, Point2D.Double P2, int order) {
        this.P1 = P1;
        this.P2 = P2;
        this.order = order;
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;
        g2d.setColor(Color.BLUE);
        drawFractal(g2d, P1, P2, order);
    }

    private void drawFractal(Graphics2D g, Point2D.Double start, Point2D.Double end, int order) {
        if (order == 0) {
            g.drawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y);
        } else {
            g.drawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y);

            // Вектор від start до end
            double dx = end.x - start.x;
            double dy = end.y - start.y;

            // Довжина гілки менша (наприклад, 70% від поточної)
            double scale = 0.7;

            // Створюємо нові кінці відгалужень під кутами ±45 градусів
            double angle1 = Math.toRadians(45);
            double angle2 = Math.toRadians(-45);

            Point2D.Double newEnd1 = new Point2D.Double(
                    end.x + (dx * Math.cos(angle1) - dy * Math.sin(angle1)) * scale,
                    end.y + (dx * Math.sin(angle1) + dy * Math.cos(angle1)) * scale
            );

            Point2D.Double newEnd2 = new Point2D.Double(
                    end.x + (dx * Math.cos(angle2) - dy * Math.sin(angle2)) * scale,
                    end.y + (dx * Math.sin(angle2) + dy * Math.cos(angle2)) * scale
            );

            drawFractal(g, end, newEnd1, order - 1);
            drawFractal(g, end, newEnd2, order - 1);
        }
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Dandelion Fractal");
        Point2D.Double P1 = new Point2D.Double(300, 350);
        Point2D.Double P2 = new Point2D.Double(300, 250);
        int order = 5; // Порядок фракталу

        DandelionFractal panel = new DandelionFractal(P1, P2, order);
        frame.add(panel);
        frame.setSize(600, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}
