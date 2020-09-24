#!/bin/bash

echo "starting simulation..."

if test ! -d files/g/; then
    mkdir files/g/
fi

if test ! -d files/g/log/; then
    mkdir files/g/log/
fi

if test ! -d files/g/dependent/; then
    mkdir files/g/dependent/
fi

if test ! -d files/g/independent/; then
    mkdir files/g/independent/
fi

if test ! -d files/g/top/; then
    mkdir files/g/top/
fi

if test -f files/g/g.dat; then
    rm files/g/g.dat
fi

# sites traps num_walkers steps mu_time max_resources eat_rate (in)dependent
#   1     2        3        4      5          6          7           8

#############################################################################################

echo "analyzing dependent walkers from 1 to 1001..."

SECONDS=0
if test ! -d files/g/dependent/trap_0/; then
    mkdir files/g/dependent/trap_0/
fi

echo "log file for number of walkers - dependent" >> files/g/log/log_numwalkers.dat
echo "num_walkers from 1 to 1001 by 3" >> files/g/log/log_numwalkers.dat
echo "sites = 1001" >> files/g/log/log_numwalkers.dat
echo "traps = 200" >> files/g/log/log_numwalkers.dat
echo "steps = 1000" >> files/g/log/log_numwalkers.dat
echo "mu_time = 10" >> files/g/log/log_numwalkers.dat
echo "max_resources = 200" >> files/g/log/log_numwalkers.dat
echo "eat_rate = 1" >> files/g/log/log_numwalkers.dat

for i in {1..1001..5}
do
    echo -ne "num_walkers = $i\r"
    ./.execute.sh 1001 200 $i 1000 10 200 1 0 3
done
echo "simulation with dependent walkers done..."
mv files/g/g.dat files/g/dependent/g_numwalkers.dat

duration=$SECONDS
echo "time elapsed: $(($duration / 60)) minutes and $(($duration % 60)) seconds" >> files/g/log/log_numwalkers.dat
echo "" >> files/g/log/log_numwalkers.dat

#############################################################################################
#
#echo "analyzing independent walkers from 1 to 501..."
#
#if test ! -d files/g/independent/trap_0/; then
#    mkdir files/g/independent/trap_0/
#fi
#
#echo "log file for number of walkers - independent" >> files/g/log/log_numwalkers.dat
#echo "num_walkers from 1 to 501 by 3" >> files/g/log/log_numwalkers.dat
#echo "sites = 1001" >> files/g/log/log_numwalkers.dat
#echo "traps = 0" >> files/g/log/log_numwalkers.dat
#echo "steps = 1000" >> files/g/log/log_numwalkers.dat
#echo "mu_time = 10" >> files/g/log/log_numwalkers.dat
#echo "max_resources = 200" >> files/g/log/log_numwalkers.dat
#echo "eat_rate = 1" >> files/g/log/log_numwalkers.dat
#
#for i in {1..501..3}
#do
#    echo -ne "num_walkers = $i\r"
#    ./.execute.sh 1001 0 $i 1000 10 200 1 1 3
#done
#echo "simulation with independent walkers done..."
#mv files/g/g.dat files/g/independent/trap_0/g_numwalkers.dat
#
#duration=$SECONDS
#echo "time elapsed: $(($duration / 60)) minutes and $(($duration % 60)) seconds" >> files/g/log/log_numwalkers.dat
#echo "" >> files/g/log/log_numwalkers.dat
#
##############################################################################################

echo "analyzing dependent steps from 1 to 2001..."

SECONDS=0

echo "log file for number of steps - dependent" >> files/g/log/log_steps.dat
echo "steps from 1 to 2001 by 10" >> files/g/log/log_steps.dat
echo "num_walkers = 250" >> files/g/log/log_steps.dat
echo "sites = 1001" >> files/g/log/log_steps.dat
echo "traps = 200" >> files/g/log/log_steps.dat
echo "mu_time = 10" >> files/g/log/log_steps.dat
echo "max_resources = 200" >> files/g/log/log_steps.dat
echo "eat_rate = 1" >> files/g/log/log_steps.dat

for i in {1..2001..10}
do
    echo -ne "steps = $i\r"
    ./.execute.sh 1001 200 250 $i 10 200 1 0 4
done
echo "simulation with dependent steps done..."
mv files/g/g.dat files/g/dependent/g_steps.dat

duration=$SECONDS
echo "time elapsed: $(($duration / 60)) minutes and $(($duration % 60)) seconds" >> files/g/log/log_steps.dat
echo "" >> files/g/log/log_steps.dat

#############################################################################################
#
#echo "analyzing independent steps from 1 to 1201..."
#
#SECONDS=0
#
#echo "log file for number of steps - independent" >> files/g/log/log_steps.dat
#echo "steps from 1 to 1201 by 10" >> files/g/log/log_steps.dat
#echo "num_walkers = 250" >> files/g/log/log_steps.dat
#echo "sites = 1001" >> files/g/log/log_steps.dat
#echo "traps = 0" >> files/g/log/log_steps.dat
#echo "mu_time = 10" >> files/g/log/log_steps.dat
#echo "max_resources = 200" >> files/g/log/log_steps.dat
#echo "eat_rate = 1" >> files/g/log/log_steps.dat
#
#for i in {1..1202..10}
#do
#    echo -ne "steps = $i\r"
#    ./.execute.sh 1001 0 250 $i 10 200 1 1 4
#done
#echo "simulation with independent steps done..."
#mv files/g/g.dat files/g/independent/trap_0/g_steps.dat
#
#duration=$SECONDS
#echo "time elapsed: $(($duration / 60)) minutes and $(($duration % 60)) seconds" >> files/g/log/log_steps.dat
#echo "" >> files/g/log/log_steps.dat
#
#############################################################################################

echo "analyzing dependent mu_time from 1 to 71..."

SECONDS=0

echo "log file for mu_time - dependent" >> files/g/log/log_mutime.dat
echo "mu_time from 1 to 71 by 2" >> files/g/log/log_mutime.dat
echo "num_walkers = 250" >> files/g/log/log_mutime.dat
echo "sites = 1001" >> files/g/log/log_mutime.dat
echo "traps = 200" >> files/g/log/log_mutime.dat
echo "steps = 1000" >> files/g/log/log_mutime.dat
echo "max_resources = 200" >> files/g/log/log_mutime.dat
echo "eat_rate = 1" >> files/g/log/log_mutime.dat

for i in {1..71..2}
do
    echo -ne "mu_time = $i\r"
    ./.execute.sh 1001 200 250 1000 $i 200 1 0 5
done
echo "simulation with dependent mu_time done..."
mv files/g/g.dat files/g/dependent/g_mutime.dat

duration=$SECONDS
echo "time elapsed: $(($duration / 60)) minutes and $(($duration % 60)) seconds" >> files/g/log/log_mutime.dat
echo "" >> files/g/log/log_mutime.dat

#############################################################################################
#
#echo "analyzing independent mu_time from 1 to 101..."
#
#SECONDS=0
#
#echo "log file for mu_time - independent" >> files/g/log/log_mutime.dat
#echo "mu_time from 1 to 101 by 2" >> files/g/log/log_mutime.dat
#echo "num_walkers = 250" >> files/g/log/log_mutime.dat
#echo "sites = 1001" >> files/g/log/log_mutime.dat
#echo "traps = 0" >> files/g/log/log_mutime.dat
#echo "steps = 1000" >> files/g/log/log_mutime.dat
#echo "max_resources = 200" >> files/g/log/log_mutime.dat
#echo "eat_rate = 1" >> files/g/log/log_mutime.dat
#
#for i in {1..102..2}
#do
#    echo -ne "mu_time = $i\r"
#    ./.execute.sh 1001 0 250 1000 $i 200 1 1 5
#done
#echo "simulation with independent mu_time done..."
#mv files/g/g.dat files/g/independent/trap_0/g_mutime.dat
#
#duration=$SECONDS
#echo "time elapsed: $(($duration / 60)) minutes and $(($duration % 60)) seconds" >> files/g/log/log_mutime.dat
#echo "" >> files/g/log/log_mutime.dat
#
echo "the end!"
