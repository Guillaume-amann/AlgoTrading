
from scipy.stats import spearmanr

def spearman_correlation(dataframe_y_true, dataframe_y_pred):
    """
        Calculates the Spearman Correlation for a sample

    Args
        dataframe_y_true: Pandas Dataframe
            Dataframe containing the true values of y.
            This dataframe was obtained by reading a csv file with following instruction:
            dataframe_y_true = pd.read_csv(CSV_1_FILE_PATH, index_col=0, sep=',')

        dataframe_y_pred: Pandas Dataframe
            This dataframe was obtained by reading a csv file with following instruction:
            dataframe_y_pred = pd.read_csv(CSV_2_FILE_PATH, index_col=0, sep=',')

    Returns
        score: Float
            The metric evaluated with the two dataframes. This must not be NaN.
    """

    score = spearmanr(dataframe_y_true['TARGET'], dataframe_y_pred['TARGET']).correlation

    return score


