% Load your audio file
file_name = '36-a_lhl.wav';
[x, fs] = audioread(file_name);

% Initialize a count for zero crossings
zero_crossings = 0;

% Loop through the audio samples and count zero crossings
for i = 2:length(x)
    if (x(i) >= 0 && x(i-1) < 0) || (x(i) < 0 && x(i-1) >= 0)
        zero_crossings = zero_crossings + 1;
    end
end

% Display the number of zero crossings
fprintf('Number of zero crossings: %d\n', zero_crossings);

% Plot the zero crossings (optional)
figure;
plot(x);
hold on;
stem(zeros(size(x)), 'r', 'DisplayName', 'Zero Crossing');
title('Zero Crossings in the Audio Signal');
xlabel('Sample Index');
ylabel('Amplitude');
legend('Audio Signal', 'Zero Crossing');
