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
public class TextView extends javax.swing.JPanel implements Observer {
    private JTextField radius=new JTextField(20);
    private JTextField volume=new JTextField(20);
    private JTextField surfaceArea=new JTextField(20);
    
    /** Creates a new instance of TextView */
    public TextView() {
        this.setLayout(new GridLayout(6,2));
        this.setSize(200, 200);
        this.add(new JLabel("Radius = "));
        this.add(radius);
        this.add(new JLabel());
        this.add(new JLabel());
        this.add(new JLabel("Volume = "));
        this.add(volume);
        this.add(new JLabel());
        this.add(new JLabel());
        this.add(new JLabel("Surface Area = "));
        this.add(surfaceArea);
        this.add(new JLabel());
        this.add(new JLabel());
    }
    
    public void update(Observable o, Object arg) {
        SphereModel s=(SphereModel)o;
        java.text.DecimalFormat df=new java.text.DecimalFormat("0.000");//设置显示精度
        radius.setText(df.format(s.getRadius()));
        volume.setText(df.format(s.volume()));
        surfaceArea.setText(df.format(s.surfaceArea()));
    }
    
    public JTextField getTextField() {
        return radius;
    }
    
}

