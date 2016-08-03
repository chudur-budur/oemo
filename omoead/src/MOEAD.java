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

import org.uma.jmetal.algorithm.multiobjective.moead.AbstractMOEAD;
import org.uma.jmetal.algorithm.multiobjective.moead.util.MOEADUtils;
import org.uma.jmetal.operator.CrossoverOperator;
import org.uma.jmetal.operator.MutationOperator;
import org.uma.jmetal.operator.impl.crossover.DifferentialEvolutionCrossover;
import org.uma.jmetal.problem.Problem;
import org.uma.jmetal.problem.ConstrainedProblem;
import org.uma.jmetal.solution.DoubleSolution;

import java.util.*;
import java.io.* ;

/**
 * Class implementing the MOEA/D-DE algorithm described in :
 * Hui Li; Qingfu Zhang, "Multiobjective Optimization Problems With Complicated Pareto Sets,
 * MOEA/D and NSGA-II," Evolutionary Computation, IEEE Transactions on , vol.13, no.2, pp.284,302,
 * April 2009. doi: 10.1109/TEVC.2008.925798
 *
 * @author Antonio J. Nebro
 * @version 1.0
 */
@SuppressWarnings("serial")
public class MOEAD extends AbstractMOEAD<DoubleSolution>
{
	private DifferentialEvolutionCrossover differentialEvolutionCrossover ;
	public static String runUid = "1234567890" ;

	public MOEAD(Problem<DoubleSolution> problem,
	             int populationSize,
	             int resultPopulationSize,
	             int maxEvaluations,
	             MutationOperator<DoubleSolution> mutation,
	             CrossoverOperator<DoubleSolution> crossover,
	             FunctionType functionType,
	             String dataDirectory,
	             double neighborhoodSelectionProbability,
	             int maximumNumberOfReplacedSolutions,
	             int neighborSize)
	{
		super(problem, populationSize, resultPopulationSize, maxEvaluations, 
			crossover, mutation, functionType, dataDirectory, 
			neighborhoodSelectionProbability, maximumNumberOfReplacedSolutions,
			neighborSize);
		differentialEvolutionCrossover = (DifferentialEvolutionCrossover)crossoverOperator ;
	}

	@Override public void run()
	{
		initializePopulation() ;
		initializeUniformWeight();
		initializeNeighborhood();
		initializeIdealPoint() ;

		evaluations = populationSize ;
		int gen = 1 ;
		int nobj = population.get(0).getNumberOfObjectives();
		int nreal = population.get(0).getNumberOfVariables();
		int nconst = 0 ;
		if(problem instanceof ConstrainedProblem)
			nconst = ((ConstrainedProblem)problem).getNumberOfConstraints();

		try {
			File file = new File("all_pop-" + runUid + ".out");
			BufferedWriter writer = new BufferedWriter(new FileWriter(file));
			writer.write("# This file contains the data of all generations\n");
			writer.write("# of objectives = " + nobj 
					+ ", # of constraints = " + nconst 
					+ ", # of variables = " + nreal +"\n");
			do
			{
				int[] permutation = new int[populationSize];
				MOEADUtils.randomPermutation(permutation, populationSize);

				for (int i = 0; i < populationSize; i++)
				{
					int subProblemId = permutation[i];

					NeighborType neighborType = chooseNeighborType() ;
					List<DoubleSolution> parents = parentSelection(subProblemId, 
							neighborType) ;

					differentialEvolutionCrossover
						.setCurrentSolution(population.get(subProblemId));
					List<DoubleSolution> children = differentialEvolutionCrossover
						.execute(parents);

					DoubleSolution child = children.get(0) ;
					mutationOperator.execute(child);
					problem.evaluate(child);

					evaluations++;

					updateIdealPoint(child);
					updateNeighborhood(child, subProblemId, neighborType);
				}
				
				writer.write("# gen = " + gen + "\tfe = " + evaluations + "\n");
				Utils.dumpSolutionSet(population, writer, gen, evaluations);
				gen++ ;
			}
			while (evaluations < maxEvaluations);
			writer.write("# gen = " + gen + "\tfe = " + evaluations + "\n");
			Utils.dumpSolutionSet(population, writer, gen, evaluations);
			writer.close();
		} catch(Exception e) { e.printStackTrace(); }
	}

	protected void initializePopulation()
	{
		for (int i = 0; i < populationSize; i++)
		{
			DoubleSolution newSolution = (DoubleSolution)problem.createSolution();

			problem.evaluate(newSolution);
			population.add(newSolution);
		}
	}

	@Override public String getName()
	{
		return "MOEAD" ;
	}

	@Override public String getDescription()
	{
		return "Multi-Objective Evolutionary Algorithm based on Decomposition" ;
	}
}
