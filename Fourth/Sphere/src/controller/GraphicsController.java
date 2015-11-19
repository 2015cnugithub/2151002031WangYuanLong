package controller;
import java.awt.event.ActionEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import javax.swing.JTextField;

import model.SphereModel;


public class GraphicsController implements MouseListener{
	private SphereModel sphere;
	private int x1;
	private int y1;
	private int x2;
	private int y2;
	private double variation;
	/** Creates a new instance of TextController */
    public GraphicsController(SphereModel sphere) {
        this.sphere=sphere;
    }
    
    public void mousePerformed(MouseEvent e){
    	JTextField t = (JTextField)e.getSource();
    	variation=Math.sqrt(this.x1*this.x2+this.y1*this.y2);
        double r = variation;
        sphere.setRadius(r);
    }
    
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
	}
	@Override
	public void mousePressed(MouseEvent e) {
		this.x1=e.getX();
		this.y1=e.getY();
	}
	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		this.x2=e.getX();
		this.y2=e.getY();
		this.variation=Math.sqrt((this.x2-this.x1)*(this.x2-this.x1)+(this.y2-this.y1)*(this.y2-this.y1));
		if(this.x2>this.x1||this.y2>this.y1){
			sphere.setRadius(sphere.getRadius()+this.variation);
		}else{
			sphere.setRadius(sphere.getRadius()-this.variation);
		}
		
	}
	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
	}
	@Override
	public void mouseExited(MouseEvent e) {	
	}
}
