import org.uma.jmetal.solution.Solution;
import org.uma.jmetal.solution.DoubleSolution;
import org.uma.jmetal.problem.Problem;
import org.uma.jmetal.util.pseudorandom.JMetalRandom;

import java.util.*;
import java.io.* ;

public class LocalSearch
{
	private String problemName = "" ;
	private Problem<DoubleSolution> problem ;
	private ArrayList<ArrayList<Double>> chimps ;
	private ArrayList<Integer> chimIndices ;
	private int chimEvals = 0 ;
	private JMetalRandom rng ;

	LocalSearch(Problem<DoubleSolution> problem)
	{
		this.chimps = new ArrayList<ArrayList<Double>>();
		this.problem = problem ;
		this.rng = JMetalRandom.getInstance();
		this.chimIndices = new ArrayList<Integer>();
	}

	public void selectRandomCHIMBounds()
	{
		int nreal = this.problem.getNumberOfVariables();
		int nobj = this.problem.getNumberOfObjectives();
		int rindex = this.rng.nextInt(0, ((int)this.chimps.size() / nobj) - 1);
		int index = nobj * rindex ;
		System.out.println("LocalSearch.selectCHIMBounds():" 
				+ " rindex: " + rindex + " index: " + index);
		this.chimEvals = 0 ;
		String indices = "" ;
		for(int i = index ; i < index + nobj ; i++)
		{
			this.chimEvals += ((Double)this.chimps.get(i).get(nreal + nobj)).doubleValue();
			this.chimIndices.add(new Integer(i));
			indices = indices + (i+1) + ", " ; 
		}
		System.out.println("LocalSearch.selectCHIMBounds():" 
				+ " indices: " + indices + " sum FE: " + this.chimEvals);
	}

	public int getCHIMEvals() { return this.chimEvals ; }

	public void injectCHIMBounds(List<? extends Solution<?>> pop)
	{
		int nreal = this.problem.getNumberOfVariables();
		int nobj = this.problem.getNumberOfObjectives();
		for(int i = 0 ; i < this.chimIndices.size() ; i++)
		{
			for(int j = 0 ; j < nreal ; j++)
				((DoubleSolution)pop.get(i)).setVariableValue(j, 
						((Double)this.chimps
						 	.get(this.chimIndices.get(i).intValue())
							.get(j)).doubleValue());
			for(int j = nreal ; j < nreal + nobj ; j++)
				((DoubleSolution)pop.get(i)).setObjective(j - nreal, 
						((Double)this.chimps
						 .get(this.chimIndices.get(i).intValue())
						 .get(j)).doubleValue());
		}
	}

	public void loadCHIMBoundsFromFile()
	{
		String fileName = "chimps/" + this.problem.getName().toLowerCase() + "-chimps.out" ;
		try {
			BufferedReader reader = new BufferedReader(new FileReader(new File(fileName)));
			String line = "" ;
			while((line = reader.readLine()) != null) {
				String[] vals = line.split("\\s+");
				ArrayList<Double> vec = new ArrayList<Double>();
				for(int i = 0 ; i < vals.length ; i++)
					vec.add(new Double(vals[i]));
				this.chimps.add(vec);
			}
			reader.close();
			System.out.println("LocalSearch.loadCHIMBoundsFromFile():" 
					+ " CHIM+ loaded from: " + fileName);
		} catch(Exception e) { e.printStackTrace(); System.exit(1); }
	}	
}
