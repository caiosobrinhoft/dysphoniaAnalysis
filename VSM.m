% Load the WAV file and extract 2500 raw data samples
[y, fs] = audioread('1984-a_n.wav');
raw_data = y(1:2500);

% Define wavelet parameters
wavelet_name = 'db10';
level = 4;
support_size = 20;

% Perform DWT
[C, L] = wavedec(raw_data, level, wavelet_name);

% Extract the four detail coefficients
D1 = detcoef(C, L, 1);
D2 = detcoef(C, L, 2);
D3 = detcoef(C, L, 3);
D4 = detcoef(C, L, 4);

% Reconstruct RD1 (original signal from D1 only)
A1 = appcoef(C, L, wavelet_name, level);
D1_reconstructed = wrcoef('d', C, L, wavelet_name, 1);
RD1 = idwt(D1_reconstructed, [], wavelet_name, L(1));

% Reconstruct RD2 (original signal from D2 only)
D2_reconstructed = wrcoef('d', C, L, wavelet_name, 2);
RD2 = idwt(D2_reconstructed, [], wavelet_name, L(1));

% Reconstruct RD3 (original signal from D3 only)
D3_reconstructed = wrcoef('d', C, L, wavelet_name, 3);
RD3 = idwt(D3_reconstructed, [], wavelet_name, L(1));

% Reconstruct RD4 (original signal from D4 only)
D4_reconstructed = wrcoef('d', C, L, wavelet_name, 4);
RD4 = idwt(D4_reconstructed, [], wavelet_name, L(1));

% Now you have RD1, RD2, RD3, and RD4, which are the reconstructed signals from D1, D2, D3, and D4, respectively.

% Find the maximum absolute value among all RD signals
max_amplitude = max(max(abs([RD1, RD2, RD3, RD4])));

% Normalize each RD signal
RD1_normalized = RD1 / max_amplitude;
RD2_normalized = RD2 / max_amplitude;
RD3_normalized = RD3 / max_amplitude;
RD4_normalized = RD4 / max_amplitude;

% Calculate LPC coefficients for each of the RD signals
order = min(200, length(RD1_normalized) - 1);
lpc_RD1 = lpc(RD1_normalized, order);
order = min(200, length(RD2_normalized) - 1);
lpc_RD2 = lpc(RD2_normalized, order);
order = min(200, length(RD3_normalized) - 1);
lpc_RD3 = lpc(RD3_normalized, order);
order = min(200, length(RD4_normalized) - 1);
lpc_RD4 = lpc(RD4_normalized, order);

% Apply the LPC inverse filter to each RD signal
filtered_RD1 = filter(lpc_RD1, 1, RD1_normalized);
filtered_RD2 = filter(lpc_RD2, 1, RD2_normalized);
filtered_RD3 = filter(lpc_RD3, 1, RD3_normalized);
filtered_RD4 = filter(lpc_RD4, 1, RD4_normalized);

% ... (Previous code to calculate RD signals and normalize them)

% Calculate RMS values for each reconstructed signal
RMSRD1 = rms(RD1_normalized);
RMSRD2 = rms(RD2_normalized);
RMSRD3 = rms(RD3_normalized);
RMSRD4 = rms(RD4_normalized);

% Display RMS values
fprintf('RMSRD1: %.4f\n', RMSRD1);
fprintf('RMSRD2: %.4f\n', RMSRD2);
fprintf('RMSRD3: %.4f\n', RMSRD3);
fprintf('RMSRD4: %.4f\n', RMSRD4);

% Create a feature matrix where each row is a data point and each column is a feature
feature_matrix = [RMSRD1, RMSRD2, RMSRD3, RMSRD4];

% Ensure that the dimensions of training_data and training_labels match
training_data = [RMSRD1; RMSRD2; RMSRD3; RMSRD4]; % Concatenate RMS values as features
training_labels = [1; 1; 2; 2]; % Labels for the corresponding classes (1 and 2)

% Check if dimensions match
if size(training_data, 1) ~= length(training_labels)
    error('Number of data points does not match the number of target labels.');
end

% Specify the RBF kernel width (you can adjust this value)
rbf_width = 1.0;

% Train the LS-SVM classifier with the RBF kernel (without visualization)
model = lssvm(training_data, training_labels, 'classification', 'RBF_kernel', rbf_width, [], 'simplex');

% Make predictions using the trained LS-SVM model on new_data
% Replace 'new_data' with your actual data if you have new samples to classify
new_data = feature_matrix; % Assuming feature_matrix contains the RMS values of new data
predictions = predict(model, new_data);



% Define a threshold (you can adjust this threshold based on your problem)
threshold = 0.5;

% Apply the threshold to classify as normal (1) or pathological (2)
results = (predictions >= threshold) + 1;

% Display the results (1 for normal, 2 for pathological)
fprintf('Results:\n');
for i = 1:length(results)
    if results(i) == 1
        fprintf('Sample %d: Normal\n', i);
    else
        fprintf('Sample %d: Pathological\n', i);
    end
end




