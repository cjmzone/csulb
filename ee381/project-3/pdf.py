from fpdf import FPDF

# Initialize PDF
pdf = FPDF()
pdf.set_auto_page_break(auto=True, margin=15)
pdf.add_page()
pdf.set_font("Arial", "B", 14)

# Title
pdf.cell(0, 10, "Project Report: Bernoulli Trials and Probability Distributions", ln=True, align="C")
pdf.ln(10)

# Section 1: Experimental Bernoulli Trials
pdf.set_font("Arial", "B", 12)
pdf.cell(0, 10, "1. Experimental Bernoulli Trials", ln=True)
pdf.set_font("Arial", "", 12)
pdf.multi_cell(0, 10, "In this experiment, three identical 5-sided unfair dice were rolled 1,000 times for each trial. "
                      "If all three dice showed '1', it was considered a success. The experiment was repeated 10,000 "
                      "times to generate a probability distribution based on the number of successes in each trial.")
pdf.ln(5)
pdf.image("/mnt/data/1.png", w=150)  # Insert experimental result graph

# Section 2: Calculations using the Binomial Distribution
pdf.set_font("Arial", "B", 12)
pdf.cell(0, 10, "2. Calculations using the Binomial Distribution", ln=True)
pdf.set_font("Arial", "", 12)
pdf.multi_cell(0, 10, "Using the Binomial formula, the probability distribution function for the random variable X "
                      "(number of successes in 1,000 Bernoulli trials) was calculated. The plot below shows the "
                      "theoretical distribution based on the Binomial formula.")
pdf.ln(5)
pdf.image("/mnt/data/2.png", w=150)  # Insert Binomial distribution graph

# Section 3: Approximation of Binomial by Poisson Distribution
pdf.set_font("Arial", "B", 12)
pdf.cell(0, 10, "3. Approximation of Binomial by Poisson Distribution", ln=True)
pdf.set_font("Arial", "", 12)
pdf.multi_cell(0, 10, "Given that the probability of success in a single trial is small and the number of trials is large, "
                      "the Poisson distribution was used as an approximation of the Binomial distribution. The plot "
                      "below represents the probability distribution using the Poisson approximation.")
pdf.ln(5)
pdf.image("/mnt/data/3.png", w=150)  # Insert Poisson approximation graph

# Save PDF
pdf.output("/mnt/data/Bernoulli_Trials_Report.pdf")

