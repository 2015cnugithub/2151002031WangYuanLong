package controller;

/**
 *
 * @author wangyuanlong
 */

import javax.swing.*;

import model.SphereModel;

import java.awt.*;
import java.awt.event.*;

public class TextController implements ActionListener{

    private SphereModel sphere;
    
    /** Creates a new instance of TextController */
    public TextController(SphereModel sphere) {
        this.sphere=sphere;
    }
    
    public void actionPerformed(ActionEvent e) {
        JTextField t = (JTextField)e.getSource();
        double r = Double.parseDouble(t.getText());
        sphere.setRadius(r);
    }

}
