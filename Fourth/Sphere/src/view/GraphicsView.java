package view;

/**
 *
 * @author wangyuanlong
 */


import java.util.Observer;
import java.util.Observable;
import javax.swing.*;

import model.SphereModel;

import java.awt.*;

public class GraphicsView extends javax.swing.JPanel implements Observer {
    
    private double radius=0;
    
    /** Creates a new instance of GraphicsView */
    public GraphicsView() {
        this.setSize(200, 200);
        this.setBackground(new Color(255,255,255));
        
    }
    
    public void update(Observable o, Object arg) {
        SphereModel s=(SphereModel)o;
        radius=s.getRadius();
        repaint();
    }
   
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        int r=(int)radius;
        int r1=(int)radius*2;
        int r2=(int)radius/2;
        g.drawOval(0, 0, r1, r1);
        g.drawOval(r2, 0, r, r1);
        g.drawOval(0, r2, r1, r);

    }
    
    
}
