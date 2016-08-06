import org.uma.jmetal.solution.Solution;
import org.uma.jmetal.solution.DoubleSolution;
import org.uma.jmetal.problem.Problem;
import org.uma.jmetal.util.pseudorandom.JMetalRandom;

import java.util.*;
import java.io.* ;

public class LocalSearch
{
	private String problemName = "" ;
	private ArrayList<ArrayList<Double>> chimps ;
	private Problem<DoubleSolution> problem ;
	private JMetalRandom rng ;

	LocalSearch(Problem<DoubleSolution> problem)
	{
		this.chimps = new ArrayList<ArrayList<Double>>();
		this.problem = problem ;
		this.rng = JMetalRandom.getInstance();
	}

	public int injectCHIMBounds(List<? extends Solution<?>> pop)
	{
		int nreal = pop.get(0).getNumberOfVariables();
		int nobj = pop.get(0).getNumberOfObjectives();
		int index = nobj * this.rng.nextInt(0, this.chimps.size() / nobj);
		int fe = 0 ;
		/*for(int i = 0 ; i < this.chimps.size() ; i++)
		{
			for(int j = 0 ; j < this.chimps.get(i).size() ; j++)
				System.out.print(this.chimps.get(i).get(j) + "\t");
			System.out.println();
		}*/
		String indices = "" ;
		for(int i = index, k = 0  ; i < index + nobj ; i++, k++)
		{
			for(int j = 0 ; j < nreal ; j++)
				((DoubleSolution)pop.get(k)).setVariableValue(j, 
						((Double)this.chimps.get(i).get(j)).doubleValue());
			for(int j = nreal ; j < nreal + nobj ; j++)
				((DoubleSolution)pop.get(k)).setObjective(j - nreal, 
						((Double)this.chimps.get(i).get(j)).doubleValue());
			fe += ((Double)this.chimps.get(i).get(nreal + nobj)).doubleValue();
			indices = indices + (i+1) + ", " ; 
		}
		System.out.println("LocalSearch.injectCHIMBounds(): indices: " + indices + " sum FE: " + fe);
		return fe ;
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
