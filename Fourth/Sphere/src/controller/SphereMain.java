package controller;

/**
 *
 * @author wangyuanlong
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

import javax.swing.event.*;

import view.GraphicsView;
import view.TextView;


import model.SphereModel;


/**
 *
 * @author  Administrator
 */
public class SphereMain extends JFrame {
    
    /** Creates a new instance of SphereMain */
    public SphereMain() {
        super("mvc");
        setSize(400,200);
        setLocation(Toolkit.getDefaultToolkit().getScreenSize().width/2-200, Toolkit.getDefaultToolkit().getScreenSize().height/2-200);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        SphereModel sphere=new SphereModel(50);
        TextView textView=new TextView();
        GraphicsView graphicsView=new GraphicsView();

        textView.getTextField().addActionListener(new TextController(sphere));
        graphicsView.addMouseListener((MouseListener) new GraphicsController(sphere));//添加一个图形区的监听器
        sphere.addObserver(textView);
        sphere.addObserver(graphicsView);

        Container c=getContentPane();
        c.setLayout(new GridLayout(1,2));
        c.add(textView);
        c.add(graphicsView);
        textView.update(sphere, null);
        graphicsView.update(sphere,null);
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        new SphereMain().show();
    }
    
}
