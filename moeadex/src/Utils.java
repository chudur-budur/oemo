import org.uma.jmetal.solution.Solution;
import org.uma.jmetal.solution.DoubleSolution;
import org.uma.jmetal.problem.Problem;
import org.uma.jmetal.util.solutionattribute.Ranking;
import org.uma.jmetal.util.solutionattribute.impl.DominanceRanking;
import org.uma.jmetal.util.solutionattribute.impl.CrowdingDistance;
import org.uma.jmetal.util.JMetalLogger;
import org.uma.jmetal.util.pseudorandom.JMetalRandom;
import java.util.*;
import java.io.* ;

public class Utils<S extends Solution<?>>
{
	public void dumpSolutionSet(List<S> solutionList, 
			BufferedWriter writer, int gen, int fe)
	{
		try {
			if (solutionList.size() > 0) 
			{
				int nreal = solutionList.get(0).getNumberOfVariables();
				int nobj = solutionList.get(0).getNumberOfObjectives();
				
				Ranking<S> ranking = this.computeRanking(solutionList);
				
				for(int f = 0 ; f < ranking.getNumberOfSubfronts(); f++)
				{
					List<S> subfront = ranking.getSubfront(f);
					this.computeCrowdingDistance(subfront);
					for(int i = 0 ; i < subfront.size() ; i++)
					{
						for(int j = 0 ; j < nobj ; j++)
							writer.write(String.format("%1$.3f\t", 
								subfront.get(i).getObjective(j)));
						for(int j = 0 ; j < nreal ; j++)
							writer.write(String.format("%1$.3f\t", 
								subfront.get(i).getVariableValue(j)));
						// print constraint violation
						writer.write("0.000\t");
						// print rank
						writer.write(String.format("%1$d\t", f+1));
						// print crowd. dist
						Double cd = (double)subfront.get(i)
							.getAttribute(CrowdingDistance.class);
						if(cd == Double.POSITIVE_INFINITY) cd = 1.00e+14 ;
						writer.write(String.format("%1$1.2e\t", cd));
						// print is_opposite
						writer.write("0");
						// line break
						writer.newLine();
					}
				}
			}
		} 
		catch(Exception e) { e.printStackTrace(); }	
		JMetalLogger.logger.info("Random seed: " + JMetalRandom.getInstance().getSeed());
		JMetalLogger.logger.info("Solutions at gen: " + gen + ", fe: " + fe 
				+ " have been saved to file.");
	}

	private Ranking<S> computeRanking(List<S> solutionList) 
	{
		Ranking<S> ranking = new DominanceRanking<S>();
		ranking.computeRanking(solutionList);
		return ranking;
	}

	private void computeCrowdingDistance(List<S> solutionList)
	{
		CrowdingDistance<S> crowdingDistance = new CrowdingDistance<S>();
		crowdingDistance.computeDensityEstimator(solutionList);
	}

	public String[] mapResources(String problemName)
	{
		String[] res = new String[2] ;
		// resource from jar needs to start with a slash "/" -- weird
		if(problemName.toLowerCase().matches("dtlz.*"))
		{
			res[0] = "org.uma.jmetal.problem.multiobjective.dtlz." 
				+ problemName.toUpperCase();
			res[1] = "/pareto_fronts/" + problemName.toUpperCase() + ".3D.pf" ;
		}
		else if(problemName.toLowerCase().matches("zdt.*"))
		{
			res[0] = "org.uma.jmetal.problem.multiobjective.zdt." 
				+ problemName.toUpperCase();
			res[1] = "/pareto_fronts/" + problemName.toUpperCase() + ".pf" ;
		}
		else {
			System.err.println("Utils.mapProblemName(): " 
					+ "problem \'" + problemName + "\' is not yet mappable.");
			System.exit(1);
		}
		try {
			Class cls = Class.forName(res[0], false, Problem.class.getClassLoader());
		} catch(Exception e) { e.printStackTrace(); System.exit(1); }
		return res ;
	}

	public int[] getParams(String problemName)
	{
		String set1 = "zdt4,zdt6" ;
		String set2 = "dtlz7" ;
		int[] params = new int[2] ;
		if(set1.contains(problemName.toLowerCase()))
		{
			params[0] = 100 ; // popsize
			params[1] = 20000 ; // evals
		}
		else if(set2.contains(problemName.toLowerCase()))
		{
			params[0] = 200 ; // popsize
			params[1] = 40000 ; // evals
		}
		else {
			System.err.println("Utils.getParams(): " 
					+ "nothing is specified for problem \'" + problemName + "\'.");
			System.exit(1);
		}
		return params ;
	}
}
