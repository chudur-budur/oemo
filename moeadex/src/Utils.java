import org.uma.jmetal.solution.Solution;
import org.uma.jmetal.solution.DoubleSolution;
import org.uma.jmetal.problem.Problem;
import org.uma.jmetal.util.JMetalLogger;
import org.uma.jmetal.util.pseudorandom.JMetalRandom;

import java.util.*;
import java.io.* ;

public class Utils
{
	public static void dumpSolutionSet(List<? extends Solution<?>> solutionList, 
			BufferedWriter writer, int gen, int fe)
	{
		try {
			if (solutionList.size() > 0) 
			{
				int nreal = solutionList.get(0).getNumberOfVariables();
				int nobj = solutionList.get(0).getNumberOfObjectives();
				for (int i = 0; i < solutionList.size(); i++) 
				{
					for (int j = 0 ; j < nobj ; j++)
						writer.write(String.format("%1$.3f\t", 
							solutionList.get(i).getObjective(j)));
					for (int j = 0; j < nreal; j++)
						writer.write(String.format("%1$.3f\t", 
							solutionList.get(i).getVariableValue(j)));
					writer.newLine();
				}
			}
		} catch(Exception e) { e.printStackTrace(); }	
		JMetalLogger.logger.info("Random seed: " + JMetalRandom.getInstance().getSeed());
		JMetalLogger.logger.info("Solutions at gen: " + gen + ", fe: " + fe 
				+ " have been saved to file.");
	}

	public static String[] mapResources(String problemName)
	{
		String[] res = new String[2] ;
		// resource from jar needs to start with a slash "/" -- weird
		if(problemName.toLowerCase().matches("dtlz.*"))
		{
			res[0] = "org.uma.jmetal.problem.multiobjective.dtlz." + problemName.toUpperCase();
			res[1] = "/pareto_fronts/" + problemName.toUpperCase() + ".3D.pf" ;
		}
		else if(problemName.toLowerCase().matches("zdt.*"))
		{
			res[0] = "org.uma.jmetal.problem.multiobjective.zdt." + problemName.toUpperCase();
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

	public static int[] getParams(String problemName)
	{
		int[] params = new int[2] ;
		if(problemName.toLowerCase().equals("dtlz7"))
		{
			params[0] = 100 ; // popsize
			params[1] = 20000 ; // evals
		}
		else {
			System.err.println("Utils.getParams(): " 
					+ "nothing is specified for problem \'" + problemName + "\'.");
			System.exit(1);
		}
		return params ;
	}
}
