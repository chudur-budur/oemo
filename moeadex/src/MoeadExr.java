//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.


import org.uma.jmetal.algorithm.Algorithm;
import org.uma.jmetal.algorithm.multiobjective.moead.AbstractMOEAD;
import org.uma.jmetal.operator.MutationOperator;
import org.uma.jmetal.operator.impl.crossover.DifferentialEvolutionCrossover;
import org.uma.jmetal.operator.impl.mutation.PolynomialMutation;
import org.uma.jmetal.problem.DoubleProblem;
import org.uma.jmetal.solution.DoubleSolution;
import org.uma.jmetal.runner.AbstractAlgorithmRunner;
import org.uma.jmetal.util.AlgorithmRunner;
import org.uma.jmetal.util.JMetalLogger;
import org.uma.jmetal.util.ProblemUtils;
import org.uma.jmetal.util.pseudorandom.JMetalRandom;
 
import java.io.*;
import java.util.*;

/**
 * Class for configuring and running the MOEA/D algorithm
 *
 * @author Antonio J. Nebro <antonio@lcc.uma.es>
 */
public class MoeadExr extends AbstractAlgorithmRunner
{
	/**
	 * @param args Command line arguments.
	 * @throws SecurityException
	 * Invoking command:
		java -cp [your classpath] MoedExr [problem name] [seed] [outfile-uid]
	 */
	public static void main(String[] args) throws FileNotFoundException
	{

		String problemName ;
		String referenceParetoFront = "";
		long seed ;
		String outfileUid ;
		if(args.length < 3) {
			System.err.println(
				"Usage: java -cp [your classpath] MoeadExr " 
				+ "[problem name] [seed] [outfile-uid]");
			System.exit(1);
		}
		
		problemName = args[0] ;
		seed = Long.parseLong(args[1]) ;
		outfileUid = args[2];
		String[] res = Utils.mapResources(problemName);
		System.out.println("problem: " + problemName + " seed: " + seed + " uid: " + outfileUid);
		System.out.println("res[0]: " + res[0] + " res[1]: " + res[1]);	
		JMetalRandom.getInstance().setSeed(seed);
		MoeadEx.runUid = outfileUid ;
		
		DoubleProblem problem;
		Algorithm<List<DoubleSolution>> algorithm;
		MutationOperator<DoubleSolution> mutation;
		DifferentialEvolutionCrossover crossover;

		problem = (DoubleProblem)ProblemUtils.<DoubleSolution> loadProblem(res[0]);
		
		int[] params = Utils.getParams(problemName);
		int popSize = params[0] ;
		int resultPopSize = popSize ;
		int maxEval = params[1] ;
		double neighbourhoodSelectionProb = 0.9 ;
		int maxNumReplace = 2 ;
		int neighbourSize = 20 ;
		String dataDir = "MOEAD_Weights" ;

		double cr = 1.0 ;
		double f = 0.5 ;
		crossover = new DifferentialEvolutionCrossover(cr, f, "rand/1/bin");

		double mutationProbability = 1.0 / problem.getNumberOfVariables();
		double mutationDistributionIndex = 20.0;
		mutation = new PolynomialMutation(mutationProbability, mutationDistributionIndex);

		algorithm = new MoeadEx(problem, popSize, resultPopSize, maxEval, mutation, crossover,
				AbstractMOEAD.FunctionType.TCHE, dataDir, neighbourhoodSelectionProb,
				maxNumReplace, neighbourSize);

		AlgorithmRunner algorithmRunner = new AlgorithmRunner.Executor(algorithm).execute() ;

		List<DoubleSolution> population = algorithm.getResult() ;
		long computingTime = algorithmRunner.getComputingTime() ;

		JMetalLogger.logger.info("Total execution time: " + computingTime + "ms");

		if (!referenceParetoFront.equals(""))
			printQualityIndicators(population, referenceParetoFront) ;
	}
}
